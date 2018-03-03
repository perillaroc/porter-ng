#include "convert_config.h"

#include <iostream>
#include <algorithm>

#include <boost/lexical_cast.hpp>

using namespace std;
using namespace GradsToGrib;


bool ParamConfig::isLevelSet() const
{
    if(number_keys_.find("level") != end(number_keys_))
    {
        return true;
    }

    if(number_keys_.find("scaledValueOfFirstFixedSurface") != end(number_keys_))
    {
        return true;
    }

    return false;
}

double ParamConfig::calculateValue(double orig_value) {
    value_parser_->DefineVar("x", &orig_value);
    double result = value_parser_->Eval();
    value_parser_->RemoveVar("x");
    return result;
}


ConvertConfig::ConvertConfig()
{

}

void ConvertConfig::parse(const string &config_file_path)
{
    config_file_path_ = config_file_path;

    YAML::Node config = YAML::LoadFile(config_file_path_);

    YAML::Node params_node = config["params"];
    parseParams(params_node);

    YAML::Node grads_ctl_node = config["grads_ctl"];
    if(grads_ctl_node){
        parseGradsCtl(grads_ctl_node);
    }
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

void ConvertConfig::parseParams(YAML::Node &params_node) {
    for(YAML::const_iterator iter=params_node.begin(); iter != params_node.end(); iter++)
    {
        ParamConfig param_config;
        YAML::Node param_node = iter->as<YAML::Node>();
        string param_name = param_node["name"].as<string>();
        param_config.name_ = param_name;
//        cout<<param_name<<endl;

        YAML::Node levels_node = param_node["levels"];
        if(levels_node)
        {
            for (std::size_t i=0;i<levels_node.size();i++)
            {
                auto level = levels_node[i].as<double>();
                param_config.levels_.push_back(level);
            }
        }

        YAML::Node keys_node = param_node["keys"];
        for(YAML::const_iterator key_iter=keys_node.begin(); key_iter != keys_node.end(); key_iter++)
        {
            auto key_name = key_iter->first.as<string>();
            auto key_value = key_iter->second.as<string>();
            try {
                auto value_number = boost::lexical_cast<long>(key_value);
                // cout<<key_name<<" [long] "<<value_number<<endl;
                param_config.number_keys_[key_name] = value_number;
                param_config.keys_list_.emplace_back(make_pair(key_name, ConfigKeyType::Long));
            }
            catch (boost::bad_lexical_cast &b) {
                // cout<<key_name<<" [string] "<<key_value<<endl;
                param_config.string_keys_[key_name] = key_value;
                param_config.keys_list_.emplace_back(make_pair(key_name, ConfigKeyType::String));
            }
        }

        YAML::Node value_node = param_node["value"];
        if(value_node)
        {
            string value_expr = value_node.as<string>();
            auto value_parser = make_shared<mu::Parser>();
            value_parser-> SetExpr(value_expr);
            param_config.value_parser_ = value_parser;
        }

        param_configs_.push_back(param_config);
    }
}

void ConvertConfig::parseGradsCtl(YAML::Node &grads_ctl_node) {
    YAML::Node props_node = grads_ctl_node["props"];
    if(props_node)
    {
        for(YAML::const_iterator key_iter=props_node.begin(); key_iter != props_node.end(); key_iter++)
        {
            auto key_name = key_iter->first.as<string>();
            auto key_value = key_iter->second.as<string>();
            grads_ctl_props_[key_name] = key_value;
        }
    }
}
