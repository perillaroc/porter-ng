#pragma once

#include <fstream>

#include "grads_ctl.h"
#include "grads_record_handler.h"

namespace GradsParser {

    class GradsDataHandler {
    public:
        explicit GradsDataHandler(GradsCtl &grads_ctl);

        ~GradsDataHandler();

        void openDataFile();

        bool hasNext() const
        {
            return next_variable_index_ < grads_ctl_.vars_.size();
        }

        GradsRecordHandler* loadNext();

    private:
        GradsCtl grads_ctl_;

        std::ifstream data_file_stream_;
        int next_variable_index_;
    };

}
