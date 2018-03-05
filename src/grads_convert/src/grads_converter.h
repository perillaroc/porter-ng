#pragma once

#include <string>
#include <memory>
#include <vector>

#include "convert_config.h"
#include <grads_ctl.h>

namespace GradsParser
{
class GradsMessagedHandler;
}

namespace GradsConvert {

struct ConvertedMessage{
    int index_ = -1;
    ParamConfig param_config_;
};

class GradsConverter
{
public:
    GradsConverter() = default;

    void setConfigFilePath(const std::string &convert_config_file_path);
    void setCtlFilePath(const std::string &ctl_file_path);
    void setOutputFilePath(const std::string &output_file_path);

    void convert();

protected:
    GradsParser::GradsCtl getGradsCtl();

    std::vector<ConvertedMessage> getConvertedMessages(GradsParser::GradsCtl &grads_ctl);

    void convertMessages(GradsParser::GradsCtl &grads_ctl, std::vector<ConvertedMessage> &converted_messages);

    void convertMessage(std::shared_ptr<GradsParser::GradsMessagedHandler> message_handler,
                        ParamConfig &param_config, int message_count);

    std::string convert_config_file_path_;
    std::string ctl_file_path_;
    std::string output_file_path_;

    ConvertConfig convert_config_;

};

}
