#pragma once

#include <string>
#include <map>
#include <vector>

namespace GradsToGrib
{
    enum class ConfigKeyType
    {
        Long,
        String
    };

    struct ParamConfig
    {

        bool isLevelSet() const;

        std::string name_;

        std::vector<double> levels_;

        std::vector<std::pair<std::string, ConfigKeyType>> keys_list_;
        std::map<std::string, long> number_keys_;
        std::map<std::string, std::string> string_keys_;
    };


    class ConvertConfig {
    public:
        ConvertConfig();

        std::vector<ParamConfig>& paramConfigs() { return param_configs_; }

        void parse(const std::string &config_file_path);

        std::vector<ParamConfig>::iterator findParamConfig(
                const std::string &name,
                double *level = nullptr);

    private:
        std::string config_file_path_;

        std::vector<ParamConfig> param_configs_;
    };
}

