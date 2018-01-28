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

    string var_name = "u";
    double level = 1000.0;
    auto index = GradsUtil::findVariableIndex(grads_ctl, var_name, LevelType::Multi, level);
    if(index == -1)
    {
        cerr<<"can't find u at 1000hPa."<<endl;
        return 2;
    }

    GradsDataHandler data_handler{grads_ctl};
    data_handler.openDataFile();
    auto message_handler = data_handler.loadByIndex(index);

    // value
    auto message_values = message_handler->values();
    std::vector<float> values = GradsUtil::rearrangeValueMatrix(
            message_values, message_handler->xDef().count_, message_handler->yDef().count_,
            message_handler->yDef().step_, message_handler->yDef().step_);

    string data_date = GradsUtil::formatDateTime(message_handler->startTime(), "%Y%m%d");
    int start_hour = message_handler->startTime().time_of_day().hours();
    int forecast_hour = message_handler->forecastTime().hours();

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

    /*
     * significanceOfReferenceTime:
     *      0: Analysis
     *      1: Start of Forecast
     *
     *  see http://www.nco.ncep.noaa.gov/pmb/docs/grib2/grib2_table1-2.shtml
     */
    if(forecast_hour == 0)
    {
        codes_set_long(handle, "significanceOfReferenceTime", 0);
    }
    else
    {
        codes_set_long(handle, "significanceOfReferenceTime", 1);
    }

    codes_set_long(handle, "dataDate", boost::lexical_cast<long>(data_date));
    codes_set_long(handle, "dataTime", start_hour);

    codes_set_long(handle, "productionStatusOfProcessedData", 0);

    /*
     * typeOfProcessedData:
     *      0: Analysis Products
     *      1: Forecast Products
     *
     * see http://www.nco.ncep.noaa.gov/pmb/docs/grib2/grib2_table1-4.shtml
     */
    if(forecast_hour == 0)
    {
        codes_set_long(handle, "typeOfProcessedData", 0);
    }
    else
    {
        codes_set_long(handle, "typeOfProcessedData", 1);
    }

    // section 3
    codes_set_long(handle, "Ni", message_handler->xDef().count_);
    codes_set_long(handle, "Nj", message_handler->yDef().count_);

    codes_set_double(handle, "longitudeOfFirstGridPointInDegrees", message_handler->xDef().values_.front());
    codes_set_double(handle, "longitudeOfLastGridPointInDegrees", message_handler->xDef().values_.back());
    codes_set_double(handle, "iDirectionIncrementInDegrees", message_handler->xDef().step_);

    codes_set_double(handle, "latitudeOfFirstGridPointInDegrees", message_handler->yDef().values_.back());
    codes_set_double(handle, "latitudeOfLastGridPointInDegrees", message_handler->yDef().values_.front());
    codes_set_double(handle, "jDirectionIncrementInDegrees", message_handler->yDef().step_);

    // section 4
    codes_set_long(handle, "parameterCategory", 2);
    codes_set_long(handle, "parameterNumber", 2);

    /**
     * typeOfGeneratingProcess
     *  0: Analysis
     *  2: Forecast
     */
    if(forecast_hour == 0)
    {
        codes_set_long(handle, "typeOfGeneratingProcess", 0);
    }
    else
    {
        codes_set_long(handle, "typeOfGeneratingProcess", 2);
    }

    /**
     * generatingProcessIdentifier:
     *  - Analysis or forecast generating processes identifier (defined by originating centre)
     *  15
     */
    codes_set_long(handle, "generatingProcessIdentifier", 15);

    /**
     * indicatorOfUnitOfTimeRange
     *  0: Minute
     *  1: Hour
     *
     * see http://www.nco.ncep.noaa.gov/pmb/docs/grib2/grib2_table4-4.shtml
     */
    codes_set_long(handle, "indicatorOfUnitOfTimeRange", 1);
//    codes_set_long(handle, "stepUnits", 1);
    codes_set_long(handle, "forecastTime", forecast_hour);

    // set parameter's level

    /**
     * typeOfFirstFixedSurface
     *  100: Isobaric Surface
     *
     *
     * see http://www.nco.ncep.noaa.gov/pmb/docs/grib2/grib2_table4-5.shtml
     */
//    codes_set_long(handle, "typeOfFirstFixedSurface", 100);
    codes_get_size(handle, "typeOfLevel", &size);
    codes_set_string(handle, "typeOfLevel", "isobaricInPa", &size);
    //codes_set_long(handle, "scaleFactorOfFirstFixedSurface", 0);
    codes_set_long(handle, "level", long(level*100));
//    codes_set_long(handle, "scaledValueOfFirstFixedSurface", long(level*100));

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
