#pragma once

#include <fstream>
#include <memory>

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

        std::shared_ptr<GradsRecordHandler> loadNext();

        std::shared_ptr<GradsRecordHandler> loadByIndex(int index);

    private:
        GradsCtl grads_ctl_;

        std::shared_ptr<std::ifstream> data_file_stream_;
        int next_variable_index_;
    };

}
