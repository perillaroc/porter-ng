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
