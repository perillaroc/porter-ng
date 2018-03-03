#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

#include <yaml-cpp/yaml.h>
#include <muParser.h>

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
        double calculateValue(double orig_value);

        std::string name_;

        std::vector<double> levels_;

        std::vector<std::pair<std::string, ConfigKeyType>> keys_list_;
        std::map<std::string, long> number_keys_;
        std::map<std::string, std::string> string_keys_;

        std::shared_ptr<mu::Parser> value_parser_;
    };


    class ConvertConfig {
    public:
        ConvertConfig();

        std::vector<ParamConfig>& paramConfigs() { return param_configs_; }
        std::map<std::string, std::string>& gradsCtlPropsConfig() { return grads_ctl_props_; }

        void parse(const std::string &config_file_path);

        std::vector<ParamConfig>::iterator findParamConfig(
                const std::string &name,
                double *level = nullptr);

    private:
        void parseParams(YAML::Node &params_node);
        void parseGradsCtl(YAML::Node &grads_ctl_node);

        std::string config_file_path_;

        std::vector<ParamConfig> param_configs_;
        std::map<std::string, std::string> grads_ctl_props_;
    };
}

