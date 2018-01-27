#include <iostream>
#include <algorithm>
#include <memory>

#include <eccodes.h>

#include <grads_ctl_parser.h>
#include <grads_ctl_util.h>
#include <grads_data_handler.h>

using namespace std;
using namespace GradsParser;

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cout<<"Usage: simple_grib2 ctl_file_path output_grib2_file_path"<<endl;
        return 1;
    }
    string ctl_file_path{argv[1]};
    string output_file_path{argv[2]};

    GradsCtlParser parser;
    parser.parse(ctl_file_path);
    auto grads_ctl = parser.getGradsCtl();
    grads_ctl.data_endian_ = DataEndian::BigEndian;

    auto index = GradsUtil::findVariableIndex(grads_ctl, "u", LevelType::Multi, 1000.0);
    if(index == -1)
    {
        cerr<<"can't find u at 1000hPa."<<endl;
        return 2;
    }

    GradsDataHandler data_handler{grads_ctl};
    data_handler.openDataFile();
    auto record_handler = data_handler.loadByIndex(index);

    // value
    auto record_values = record_handler->values();
    std::vector<float> values = GradsUtil::rearrangeValueMatrix(
            record_values, grads_ctl.x_def_.count_, grads_ctl.y_def_.count_,
            grads_ctl.x_def_.step_, grads_ctl.y_def_.step_);

    // grib2
    int err = 0;
    size_t size = 0;

    string sample_filename = "regular_ll_pl_grib2";
    codes_handle* handle = codes_grib_handle_new_from_samples(nullptr, sample_filename.c_str());

    // section 0
    codes_set_long(handle, "discipline", 0);

    // section 1
    codes_set_long(handle, "centre", 38);
    codes_set_long(handle, "tablesVersion", 4);
    codes_set_long(handle, "localTablesVersion", 1);
    codes_set_long(handle, "significanceOfReferenceTime", 0);

    string data_date = GradsUtil::formatDateTime(grads_ctl.start_time_, "%Y%m%d");
    codes_set_long(handle, "dataDate", boost::lexical_cast<long>(data_date));

    codes_set_long(handle, "dataTime", grads_ctl.forecast_time_.hours());
    codes_set_long(handle, "productionStatusOfProcessedData", 0);
    codes_set_long(handle, "typeOfProcessedData", 0);

    // section 3
    codes_set_long(handle, "Ni", grads_ctl.x_def_.count_);
    codes_set_long(handle, "Nj", grads_ctl.y_def_.count_);

    codes_set_double(handle, "longitudeOfFirstGridPointInDegrees", grads_ctl.x_def_.values_.front());
    codes_set_double(handle, "longitudeOfLastGridPointInDegrees", grads_ctl.x_def_.values_.back());
    codes_set_double(handle, "iDirectionIncrementInDegrees", grads_ctl.x_def_.step_);

    codes_set_double(handle, "latitudeOfFirstGridPointInDegrees", grads_ctl.y_def_.values_.back());
    codes_set_double(handle, "latitudeOfLastGridPointInDegrees", grads_ctl.y_def_.values_.front());
    codes_set_double(handle, "jDirectionIncrementInDegrees", grads_ctl.y_def_.step_);

    // section 4
    codes_set_long(handle, "parameterCategory", 2);
    codes_set_long(handle, "parameterNumber", 2);
    codes_set_long(handle, "generatingProcessIdentifier", 15);

    codes_set_long(handle, "indicatorOfUnitOfTimeRange", 1);
    codes_set_long(handle, "forecastTime", grads_ctl.forecast_time_.hours());
    codes_set_long(handle, "stepUnits", 1);

    codes_set_long(handle, "typeOfFirstFixedSurface", 100);
    codes_set_long(handle, "scaleFactorOfFirstFixedSurface", 0);
    codes_set_long(handle, "scaledValueOfFirstFixedSurface", long(grads_ctl.z_def_.values_[0]*100));

    // section 5
    codes_get_size(handle, "packingType", &size);
    codes_set_string(handle, "packingType", "grid_jpeg", &size);

    // section 7
    std::vector<double> double_values(values.begin(), values.end());
    double *value_array = &double_values[0];
    codes_set_double_array(handle, "values", value_array, values.size());

    codes_write_message(handle, output_file_path.c_str(), "wb");

    codes_handle_delete(handle);

    return 0;
}
