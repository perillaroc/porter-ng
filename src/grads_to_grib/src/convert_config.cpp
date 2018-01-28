#include "convert_config.h"

#include <yaml.h>
#include <iostream>
#include <algorithm>

#include <boost/lexical_cast.hpp>

using namespace std;
using namespace GradsToGrib;

ConvertConfig::ConvertConfig()
{

}

void ConvertConfig::parse(const string &config_file_path)
{
    config_file_path_ = config_file_path;

    YAML::Node config = YAML::LoadFile(config_file_path_);
    YAML::Node params_node = config["params"];
    for(YAML::const_iterator iter=params_node.begin(); iter != params_node.end(); iter++)
    {
        ParamConfig param_config;
        YAML::Node param_node = iter->as<YAML::Node>();
        string param_name = param_node["name"].as<string>();
        param_config.name_ = param_name;
//        cout<<param_name<<endl;

        YAML::Node keys_node = param_node["keys"];
        for(YAML::const_iterator key_iter=keys_node.begin(); key_iter != keys_node.end(); key_iter++)
        {
            auto key_name = key_iter->first.as<string>();
            auto key_value = key_iter->second.as<string>();
            try {
                auto value_number = boost::lexical_cast<long>(key_value);
//                cout<<key_name<<" [long] "<<value_number<<endl;
                param_config.number_keys_[key_name] = value_number;
            }
            catch (boost::bad_lexical_cast &b) {
//                cout<<key_name<<" [string] "<<key_value<<endl;
                param_config.string_keys_[key_name] = key_value;
            }
        }
        param_configs_.push_back(param_config);
    }
    return;
}

vector<ParamConfig>::iterator
ConvertConfig::findParamConfig(const string &name, double *level)
{
    auto iter = std::begin(param_configs_);
    while(iter != std::end(param_configs_))
    {
        auto param_config = *iter;
        if(param_config.name_ != name)
        {
            ++iter;
            continue;
        }
        if(level == nullptr || param_config.levels_.empty())
        {
            break;
        }
        auto result = std::find(begin(param_config.levels_), end(param_config.levels_), *level);
        if(result != end(param_config.levels_))
        {
            break;
        }
        ++iter;
    }

    return iter;
}
