#pragma once

#include <string>
#include <map>
#include <vector>

namespace GradsToGrib
{
    struct ParamConfig
    {
        std::string name_;

        std::map<std::string, long> number_keys_;
        std::map<std::string, std::string> string_keys_;
    };


    class ConvertConfig {
    public:
        ConvertConfig();

        std::vector<ParamConfig>& paramConfigs() { return param_configs_; }

        void parse(const std::string &config_file_path);

    private:
        std::string config_file_path_;

        std::vector<ParamConfig> param_configs_;
    };
}

