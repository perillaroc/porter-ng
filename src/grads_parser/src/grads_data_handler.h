#pragma once

#include <fstream>

#include "grads_ctl.h"

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
        std::vector<float> loadNext();

    private:
        GradsCtl grads_ctl_;
        std::vector<float> current_variable_values_;

        std::ifstream data_file_stream_;
        int next_variable_index_;
    };

}
