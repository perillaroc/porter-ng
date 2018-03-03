#pragma once

#include <string>
#include <memory>

#include "convert_config.h"
#include <grads_ctl.h>

namespace GradsParser
{
    class GradsMessagedHandler;
}

namespace GradsToGrib {

    class GradsToGribConverter
    {
    public:
        GradsToGribConverter() = default;

        void setConvertConfigFilePath(const std::string &convert_config_file_path);
        void setCtlFilePath(const std::string &ctl_file_path);
        void setOutputFilePath(const std::string &output_file_path);

        void convert();

    private:
        GradsParser::GradsCtl getGradsCtl();

        void convertMessage(std::shared_ptr<GradsParser::GradsMessagedHandler> message_handler,
                            ParamConfig &param_config, int message_count);

        void applyValueExpression(const std::string &value_expr, std::vector<double> &values);

        std::string convert_config_file_path_;
        std::string ctl_file_path_;
        std::string output_file_path_;

        ConvertConfig convert_config_;
    };

}
