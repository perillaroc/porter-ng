#include "grads_data_handler.h"

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

shared_ptr<GradsMessagedHandler> GradsDataHandler::loadNext()
{
    if(next_variable_index_ == grads_ctl_.var_infos_.size())
    {
        return nullptr;
    }
    auto message_handler = make_shared<GradsMessagedHandler>(grads_ctl_, data_file_stream_);
    message_handler->setVariable(grads_ctl_.var_infos_[next_variable_index_]);
    message_handler->loadValues();

    next_variable_index_++;
    return message_handler;
}

std::shared_ptr<GradsMessagedHandler> GradsDataHandler::loadByIndex(int index)
{
    if(index >= grads_ctl_.var_infos_.size())
    {
        return shared_ptr<GradsMessagedHandler>();
    }

    auto number_of_x = grads_ctl_.x_def_.count_;
    auto number_of_y = grads_ctl_.y_def_.count_;
    auto total_number = number_of_x * number_of_y;

    auto offset =  4 * total_number * index;

    if(grads_ctl_.is_sequential_)
    {
        offset += 4 * 2 * index + 4;
    }

    data_file_stream_->seekg(offset);

    auto message_handler = make_shared<GradsMessagedHandler>(grads_ctl_, data_file_stream_);
    message_handler->setVariable(grads_ctl_.var_infos_[index]);
    message_handler->loadValues();

    next_variable_index_ = index + 1;

    return message_handler;
}
