#pragma once
#include <fstream>
#include <memory>

#include "grads_ctl.h"

namespace GradsParser {

    class GradsMessagedHandler {
    public:
        explicit GradsMessagedHandler(const GradsCtl& grads_ctl, std::shared_ptr<std::ifstream> &data_file_stream);

        void setVariable(const VariableInfo &variable)
        {
            variable_info_ = variable;
        }

        VariableInfo& variable() { return variable_info_; }

        Dimension& xDef() { return x_def_; }
        Dimension& yDef() { return y_def_; }

        boost::posix_time::ptime& startTime() { return start_time_; };
        boost::posix_time::time_duration& forecastTime() { return forecast_time_; }

        void loadValues();

        const std::vector<float>& values() const
        {
            return values_;
        }

    private:
        boost::posix_time::ptime start_time_;
        boost::posix_time::time_duration forecast_time_;

        Dimension x_def_;
        Dimension y_def_;
        VariableInfo variable_info_;
        DataEndian data_endian_;
        DataEndian local_endian_;

        std::shared_ptr<std::ifstream> data_file_stream_;

        std::vector<float> values_;
    };

}
