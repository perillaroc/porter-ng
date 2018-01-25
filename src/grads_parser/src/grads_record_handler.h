#pragma once
#include <fstream>

#include "grads_ctl.h"

namespace GradsParser {

    class GradsRecordHandler {
    public:
        explicit GradsRecordHandler(const GradsCtl& grads_ctl, std::ifstream *data_file_stream);

        void setVariable(const Variable &variable)
        {
            variable_ = variable;
        }

        void loadValues();

        const std::vector<float>& values()
        {
            return values_;
        }

    private:
        Dimension x_def_;
        Dimension y_def_;
        Variable variable_;
        DataEndian data_endian_;
        DataEndian local_endian_;

        std::ifstream *data_file_stream_;

        std::vector<float> values_;
    };

}
