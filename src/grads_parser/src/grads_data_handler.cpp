#include "grads_data_handler.h"

#include <algorithm>

using namespace GradsParser;
using namespace std;

GradsDataHandler::GradsDataHandler(GradsCtl &grads_ctl):
        grads_ctl_{grads_ctl},
        next_variable_index_{0}
{

}

GradsDataHandler::~GradsDataHandler()
{
    if(data_file_stream_->is_open())
    {
        data_file_stream_->close();
    }
}

void GradsDataHandler::openDataFile()
{
    data_file_stream_ = make_shared<ifstream>();
    data_file_stream_->open(grads_ctl_.data_file_path_, ios::in | ios::binary);
    next_variable_index_ = 0;
}

shared_ptr<GradsRecordHandler> GradsDataHandler::loadNext()
{
    if(next_variable_index_ == grads_ctl_.vars_.size())
    {
        return nullptr;
    }
    auto record_handler = make_shared<GradsRecordHandler>(grads_ctl_, data_file_stream_);
    record_handler->setVariable(grads_ctl_.vars_[next_variable_index_]);
    record_handler->loadValues();

    next_variable_index_++;
    return record_handler;
}

std::shared_ptr<GradsRecordHandler> GradsDataHandler::loadByIndex(int index)
{
    if(index >= grads_ctl_.vars_.size())
    {
        return shared_ptr<GradsRecordHandler>();
    }

    auto number_of_x = grads_ctl_.x_def_.count_;
    auto number_of_y = grads_ctl_.y_def_.count_;
    auto total_number = number_of_x * number_of_y;

    auto offset = total_number * index;

    data_file_stream_->seekg(offset);

    auto record_handler = make_shared<GradsRecordHandler>(grads_ctl_, data_file_stream_);
    record_handler->setVariable(grads_ctl_.vars_[index]);
    record_handler->loadValues();

    next_variable_index_ = index + 1;

    return record_handler;
}
