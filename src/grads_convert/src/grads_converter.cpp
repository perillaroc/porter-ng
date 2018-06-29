#include "grads_converter.h"
#include "value_expression.h"

#include <grads_ctl_parser.h>
#include <grads_ctl_util.h>
#include <grads_data_handler.h>
#include <grads_message_handler.h>

#define OPJ_STATIC
#include <eccodes.h>

#include <iostream>

using namespace std;
using namespace GradsConvert;
using namespace GradsParser;


void GradsConverter::setConfigFilePath(const string &convert_config_file_path)
{
    convert_config_file_path_ = convert_config_file_path;
}

void GradsConverter::setCtlFilePath(const string &ctl_file_path)
{
    ctl_file_path_ = ctl_file_path;
}

void GradsConverter::setOutputFilePath(const string &output_file_path)
{
    output_file_path_ = output_file_path;
}

void GradsConverter::convert()
{
    convert_config_.parse(convert_config_file_path_);

    auto grads_ctl = getGradsCtl();
    cout<<grads_ctl.start_time_<<endl;
    cout<<grads_ctl.forecast_time_<<endl;

    auto converted_messages = getConvertedMessages(grads_ctl);
    convertMessages(grads_ctl, converted_messages);
}


vector<ConvertedMessage> GradsConverter::getConvertedMessages(GradsCtl &grads_ctl) {
    vector<ConvertedMessage> converted_messages;

    auto &var_info_list = grads_ctl.var_infos_;
    auto &param_configs = convert_config_.paramConfigs();

    for(auto &var_info: var_info_list)
    {
        auto var_name = var_info.name_;
        auto level = var_info.level_;
        auto result = convert_config_.findParamConfig(var_name, &level);
        if(result == end(param_configs))
        {
            cout<<"NOT FOUND: var "<<var_name<<" at level "<<level<<endl;
            continue;
        }

        ParamConfig param_config = *result;
        cout<<"FOUND: var "<<var_name<<" at level "<<level<<endl;

        auto index = GradsUtil::findVariableIndex(grads_ctl, var_name, var_info.level_type_, level);
        ConvertedMessage m;
        m.index_ = index;
        m.param_config_ = param_config;
        converted_messages.push_back(m);
    }

    return converted_messages;
}

GradsCtl GradsConverter::getGradsCtl() {
    GradsCtlParser parser;
    parser.parse(ctl_file_path_);

    map<string, string> props_config = convert_config_.gradsCtlPropsConfig();

    if((props_config.find("start_time")!=props_config.end())
       && (props_config.find("forecast_hour")!=props_config.end()) ) {
        auto start_time_string = props_config["start_time"];
        auto forecast_hour_string = props_config["forecast_hour"];
        parser.generateTimeForGrapes(start_time_string, forecast_hour_string);
    }

    if(props_config.find("data_endian")!=props_config.end()) {
        auto data_endian = props_config["data_endian"];
        parser.parseDataEndian(data_endian);
    }

    auto grads_ctl = parser.getGradsCtl();
    return grads_ctl;
}


void GradsConverter::convertMessages(GradsCtl &grads_ctl,
                                     vector<ConvertedMessage> &converted_messages) {
    GradsDataHandler data_handler{grads_ctl};
    data_handler.openDataFile();

    int message_count = 0;
    for(auto &m: converted_messages) {
        auto message_handler = data_handler.loadByIndex(m.index_);
        cout<<"Converting..."<<endl;
        convertMessage(message_handler, m.param_config_, message_count);
        cout<<"Converting...Done"<<endl;
        message_count++;
    }
}


void GradsConverter::convertMessage(
        shared_ptr<GradsMessagedHandler> message_handler,
        ParamConfig &param_config,
        int message_count)
{
    auto level = message_handler->variable().level_;

    // value
    auto message_values = message_handler->values();
    std::vector<float> values = GradsUtil::rearrangeValueMatrix(
            message_values, message_handler->xDef().count_, message_handler->yDef().count_,
            message_handler->yDef().step_, message_handler->yDef().step_);
    std::vector<double> double_values(values.begin(), values.end());
    if(!param_config.value_expr_.empty()){
        ValueExpression value_expression{param_config.value_expr_};
        value_expression.applyToArray(double_values.begin(), double_values.end(), double_values.begin());
    }


    string data_date = GradsUtil::formatDateTime(message_handler->startTime(), "%Y%m%d");
    int start_hour = message_handler->startTime().time_of_day().hours();
    int forecast_hour = message_handler->forecastTime().hours();

    // grib2
    int err = 0;
    size_t size = 0;

    string sample_filename = "regular_ll_pl_grib2";
    codes_handle* handle = codes_grib_handle_new_from_samples(nullptr, sample_filename.c_str());

    // section 0

    // section 1
    codes_set_long(handle, "centre", 38);
    codes_set_long(handle, "tablesVersion", 4);
    codes_set_long(handle, "localTablesVersion", 1);

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

    if(forecast_hour == 0)
    {
        codes_set_long(handle, "typeOfGeneratingProcess", 0);
    }
    else
    {
        codes_set_long(handle, "typeOfGeneratingProcess", 2);
    }

    codes_set_long(handle, "generatingProcessIdentifier", 15);


    codes_set_long(handle, "indicatorOfUnitOfTimeRange", 1);
    codes_set_long(handle, "forecastTime", forecast_hour);

    map<string, string>::const_iterator string_key;
    map<string, long>::const_iterator long_key;
    for(auto key_item: param_config.keys_list_)
    {
        auto key_name = key_item.first;
        auto key_type = key_item.second;
        switch(key_type)
        {
            case ConfigKeyType::String:
                string_key = param_config.string_keys_.find(key_name);
                codes_get_size(handle, key_name.c_str(), &size);
                cout<<key_name<<": "<<string_key->second<<endl;
                codes_set_string(handle, key_name.c_str(), string_key->second.c_str(), &size);
                break;

            case ConfigKeyType::Long:
                long_key = param_config.number_keys_.find(key_name);
                cout<<key_name<<": "<<long_key->second<<endl;
                codes_set_long(handle, key_name.c_str(), long_key->second);
                break;
        }
    }

    // set parameter's level
    if(!param_config.isLevelSet())
    {
        auto type_of_level = param_config.string_keys_.at("typeOfLevel");
        if(type_of_level == "isobaricInPa")
        {
            level *= 100;
        }

        codes_set_long(handle, "level", long(level));
    }

    // section 5
    codes_get_size(handle, "packingType", &size);
    codes_set_string(handle, "packingType", "grid_jpeg", &size);

    // section 7

    double *value_array = &double_values[0];
    codes_set_double_array(handle, "values", value_array, values.size());

    const char* output_file_mode = "wb";
    if(message_count > 0)
    {
        output_file_mode = "ab";
    }

    codes_write_message(handle, output_file_path_.c_str(), output_file_mode);

    codes_handle_delete(handle);
}
