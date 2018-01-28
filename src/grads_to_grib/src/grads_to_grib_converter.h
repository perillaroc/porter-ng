#pragma once

#include <string>
#include <memory>

#include "convert_config.h"

namespace GradsParser
{
    class GradsMessagedHandler;
}

namespace GradsToGrib {

    class GradsToGribConverter
    {
    public:
        GradsToGribConverter();

        void setConvertConfigFilePath(const std::string &convert_config_file_path);
        void setCtlFilePath(const std::string &ctl_file_path);
        void setOutputFilePath(const std::string &output_file_path);

        void convert();

    private:
        void convertMessage(std::shared_ptr<GradsParser::GradsMessagedHandler> message_handler,
                            const ParamConfig &param_config, int message_count);

        std::string convert_config_file_path_;
        std::string ctl_file_path_;
        std::string output_file_path_;
    };

}
