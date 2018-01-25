#include "grads_data_handler.h"

#include <algorithm>

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

GradsDataHandler::GradsDataHandler(GradsCtl &grads_ctl):
        grads_ctl_{grads_ctl},
        current_variable_index_{0}
{

}

void GradsDataHandler::openDataFile()
{
    data_file_stream_.open(grads_ctl_.data_file_path_, ios::in | ios::binary);
    current_variable_index_ = 0;
}

vector<float> GradsDataHandler::loadNext()
{
    current_variable_values_.clear();

    auto cur_var = grads_ctl_.vars_[current_variable_index_];
    auto x_def = grads_ctl_.x_def_;
    auto y_def = grads_ctl_.y_def_;

    auto number_of_x = x_def.count_;
    auto number_of_y = y_def.count_;
    auto total_number = number_of_x * number_of_y;

    assert(data_file_stream_.is_open());

    uint32_t buffer[total_number];

//    float real_value;
//    for(auto i=0; i<total_number; i++)
//    {
//        data_file_stream_.read((char *)(&buffer), sizeof(buffer));
//        auto buffer_value = (float*)(&buffer);
//        real_value = *buffer_value;
//        if(grads_ctl_.data_endian_ != grads_ctl_.local_endian_)
//        {
//            real_value = reverseFloat(*buffer_value);
//        }
//        current_variable_values_.push_back(real_value);
//    }

    size_t total_size = sizeof(buffer);
    data_file_stream_.read((char *)buffer, sizeof(buffer));

    auto real_buffer = (float*)(buffer);

    vector<float> real_values(total_number);
    copy(real_buffer, real_buffer+total_number, real_values.begin());
    if(grads_ctl_.data_endian_ != grads_ctl_.local_endian_)
    {
        transform(real_values.begin(), real_values.end(), real_values.begin(), reverseFloat);
    }

    current_variable_values_ = real_values;

    current_variable_index_++;
    return current_variable_values_;
}


