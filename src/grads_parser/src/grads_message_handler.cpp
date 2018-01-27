#include "grads_message_handler.h"

using namespace GradsParser;
using namespace std;

// from url:
// https://stackoverflow.com/questions/2782725/converting-float-values-from-big-endian-to-little-endian/2782742
float reverseFloat(const float inFloat)
{
    float retVal;
    auto floatToConvert = ( char* ) & inFloat;
    auto returnFloat = ( char* ) & retVal;

    // swap the bytes into a temporary buffer
    returnFloat[0] = floatToConvert[3];
    returnFloat[1] = floatToConvert[2];
    returnFloat[2] = floatToConvert[1];
    returnFloat[3] = floatToConvert[0];

    return retVal;
}

GradsMessagedHandler::GradsMessagedHandler(const GradsCtl& grads_ctl, std::shared_ptr<std::ifstream> &data_file_stream):
    start_time_{grads_ctl.start_time_},
    forecast_time_{grads_ctl.forecast_time_},
    x_def_ {grads_ctl.x_def_},
    y_def_{grads_ctl.y_def_},
    data_endian_{grads_ctl.data_endian_},
    local_endian_{grads_ctl.local_endian_},
    data_file_stream_{data_file_stream}
{

}

void GradsMessagedHandler::loadValues()
{
    auto number_of_x = x_def_.count_;
    auto number_of_y = y_def_.count_;
    auto total_number = number_of_x * number_of_y;

    assert(data_file_stream_->is_open());

    uint32_t buffer;
    float real_value;
    for(auto i=0; i<total_number; i++)
    {
        data_file_stream_->read((char *)(&buffer), sizeof(buffer));
        auto buffer_value = (float*)(&buffer);
        real_value = *buffer_value;
        if(data_endian_ != local_endian_)
        {
            real_value = reverseFloat(*buffer_value);
        }
        values_.push_back(real_value);
    }

//    uint32_t buffer[total_number];
//    data_file_stream_->read((char *)buffer, sizeof(buffer));
//
//    auto real_buffer = (float*)(buffer);
//
//    vector<float> real_values(total_number);
//    copy(real_buffer, real_buffer+total_number, real_values.begin());
//    if(data_endian_ != local_endian_)
//    {
//        transform(real_values.begin(), real_values.end(), real_values.begin(), reverseFloat);
//    }
//
//    values_ = real_values;
}
