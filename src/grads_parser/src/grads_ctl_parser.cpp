#include "grads_ctl_parser.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <regex>

using namespace GradsParser;
using namespace std;
namespace alg = boost::algorithm;
namespace fs = boost::filesystem;

GradsCtlParser::GradsCtlParser():
        cur_line_no_{-1}
{

}

void GradsCtlParser::parse(const std::string &ctl_file_path) {
    ctl_file_path_ = ctl_file_path;
    grads_ctl_.ctl_file_path_ = ctl_file_path_;

    ctl_file_lines_.clear();
    ifstream ctl_file(ctl_file_path_);
    string line;
    while(getline(ctl_file, line))
    {
        ctl_file_lines_.push_back(line);
    }

    cur_line_no_ = 0;

    size_t total_lines = ctl_file_lines_.size();

    while(cur_line_no_ < total_lines)
    {
        auto cur_line = ctl_file_lines_[cur_line_no_];
        vector<string> tokens;
        alg::split(tokens, cur_line, alg::is_space(), boost::token_compress_on);
        if(!tokens.empty())
        {
            string first_word = tokens[0];
            // cout<<first_word<<endl;
            if(first_word == "dset")
            {
                parseDset(tokens);
            }
            else if(first_word == "title")
            {
                auto title = alg::trim_copy(cur_line.substr(first_word.length()));
                grads_ctl_.title_ = title;
            }
            else if(first_word == "undef")
            {
                auto undefined_value = boost::lexical_cast<double>(tokens[1]);
                grads_ctl_.undefined_value_ = undefined_value;
            }
            else if(first_word == "xdef" || first_word == "ydef" || first_word == "zdef")
            {
                parseDimension(first_word, tokens);
            }
            else if(first_word == "tdef")
            {
                parseTimeDimension(tokens);
            }
            else if(first_word == "vars")
            {
                parseVariableDefs(tokens);
            }
        }
        cur_line_no_++;
    }

    generateVariableList();

    parseFileName();
}

void GradsCtlParser::parseDset(vector<string> &tokens) {
    string data_file_path = tokens[1];
    if(data_file_path[0] == '^')
    {
        fs::path ctl_path{ctl_file_path_};
        fs::path relative_path{data_file_path.substr(1)};
        fs::path full_path = ctl_path.parent_path() / relative_path;
        data_file_path = full_path.string();
    }
    grads_ctl_.data_file_path_ = data_file_path;
}

void GradsCtlParser::parseDimension(std::string dimension_name, std::vector<std::string> &tokens) {
    auto count = boost::lexical_cast<unsigned int>(tokens[1]);
    auto dim_type = tokens[2];
    vector<double> levels(count);
    Dimension dim;

    if(dim_type == "linear")
    {
        auto start = boost::lexical_cast<double>(tokens[3]);
        auto step = boost::lexical_cast<double>(tokens[4]);
        auto n = -1;
        std::generate(levels.begin(), levels.end(), [&n, &start, &step] () {
            n = n+1;
            return start + step*n;
        });
        dim.type_ = DimensionType::Linear;
    }
    else if(dim_type == "levels")
    {
        for(int level_index=0; level_index<count; level_index++)
        {
            cur_line_no_++;
            auto cur_line = ctl_file_lines_[cur_line_no_];
            auto level = boost::lexical_cast<double>(alg::trim_copy(cur_line));
            levels[level_index] = level;
        }
        dim.type_ = DimensionType::Level;
    }

    dim.count_ = count;
    dim.values_ = levels;

    if(dimension_name == "xdef")
    {
        grads_ctl_.x_def_ = dim;
    }
    else if(dimension_name == "ydef")
    {
        grads_ctl_.y_def_ = dim;
    }
    else if(dimension_name == "zdef")
    {
        grads_ctl_.z_def_ = dim;
    }
}

void GradsCtlParser::parseTimeDimension(std::vector<std::string> &tokens)
{
    if(tokens.size() != 5)
    {
        cerr<<"Can't parse tdef:"<<ctl_file_lines_[cur_line_no_];
        return;
    }

    auto count = boost::lexical_cast<unsigned int>(tokens[1]);
    auto dim_type = tokens[2];

    vector<boost::posix_time::ptime> times(count);
    TimeDimension dim;
    dim.count_ = count;

    if(dim_type == "linear")
    {
        string start_time_token = tokens[3];

        // start time format hh[:mm]zddmmmyyyy
        auto time_facet = new boost::posix_time::time_input_facet("%Hz%d%b%Y");
        const std::locale loc = std::locale(
                std::locale::classic(), time_facet
        );
        std::istringstream is(start_time_token);
        is.imbue(loc);

        boost::posix_time::ptime cur_time;
        is >> cur_time;

        auto step_token = tokens[4];
        boost::posix_time::time_duration step_period;
        auto increment_num = boost::lexical_cast<int>(step_token.substr(0, step_token.size()-2));
        auto increment_string = step_token.substr(step_token.size()-2, step_token.size());
        if(increment_string == "mn")
        {
            step_period = boost::posix_time::minutes(increment_num);
        }
        else if(increment_string == "hr")
        {
            step_period = boost::posix_time::hours(increment_num);
        }

        for(auto i=0; i<count; i++)
        {

            times[i] = cur_time;
            cur_time += step_period;
        }
        dim.values_ = times;

        dim.type_ = DimensionType::Linear;
    }

    grads_ctl_.t_def_ = dim;

}

void GradsCtlParser::parseVariableDefs(std::vector<std::string> &tokens)
{
    assert(tokens.size() == 2);
    auto count = boost::lexical_cast<int>(tokens[1]);

    vector<VariableDefinition> var_defs;

    for(auto i = 0; i<count; i++)
    {
        cur_line_no_++;
        auto cur_line = ctl_file_lines_[cur_line_no_];
        vector<string> var_tokens;
        alg::split(var_tokens, cur_line, alg::is_space(), boost::token_compress_on);
        VariableDefinition var_def;
        var_def.name_ = var_tokens[0];
        var_def.levels_ = boost::lexical_cast<int>(var_tokens[1]);
        var_def.units_ = var_tokens[2];

        vector<string> var_description_tokens{var_tokens.begin() + 3, var_tokens.end()};
        var_def.description_ = boost::algorithm::join(var_description_tokens, " ");

        var_defs.push_back(var_def);
    }

    grads_ctl_.var_defs_ = var_defs;
}

void GradsCtlParser::generateVariableList()
{
    vector<Variable> var_list;

    for(auto cur_time: grads_ctl_.t_def_.values_)
    {
        for(auto var_def: grads_ctl_.var_defs_)
        {
            if(var_def.levels_ == 0)
            {
                Variable var;
                var.name_ = var_def.name_;
                var.level_type_ = LevelType::Single;
                var.level_ = 0;
                var.units_ = var_def.units_;
                var.description_ = var_def.description_;
                var.time_ = cur_time;
                var_list.push_back(var);
            }
            else
            {
                for(auto i=0; i<var_def.levels_; i++)
                {
                    Variable var;
                    var.name_ = var_def.name_;
                    var.level_type_ = LevelType::Multi;
                    var.level_ = grads_ctl_.z_def_.values_[i];
                    var.level_index_ = i;
                    var.units_ = var_def.units_;
                    var.description_ = var_def.description_;
                    var.time_ = cur_time;
                    var_list.push_back(var);
                }
            }
        }
    }

    grads_ctl_.vars_ = var_list;
}

void GradsCtlParser::parseFileName()
{
    {
        // model: GRAPES GFS
        // data: postvar
        regex expression{"post.ctl_(\\d{10})_(\\d{3})"};
        smatch sm;
        if (std::regex_search(ctl_file_path_, sm, expression)) {
            int count = sm.size();
            string start_hour_string = sm[1];
            string forecast_hour_string = sm[2];

            generateTimeForGrapes(start_hour_string, forecast_hour_string);
            return;
        }
    }

    {
        // model: GRAPES GFS
        // data: modelvar
        regex expression{"model.ctl_(\\d{10})_(\\d{3})"};
        smatch sm;
        if (std::regex_search(ctl_file_path_, sm, expression)) {
            int count = sm.size();
            string start_hour_string = sm[1];
            string forecast_hour_string = sm[2];

            generateTimeForGrapes(start_hour_string, forecast_hour_string);
            return;
        }
    }

    {
        // model: GRAPES MESO
        // data: postvar
        regex expression{"post.ctl_(\\d{15})"};
        smatch sm;
        if (std::regex_search(ctl_file_path_, sm, expression)) {
            int count = sm.size();
            string time_string = sm[1];

            generateTimeForGrapes(time_string.substr(0, 10), time_string.substr(10, 3));
            return;
        }
    }

    {
        // model: GRAPES MESO
        // data: modelvar
        regex expression{"model.ctl_(\\d{15})"};
        smatch sm;
        if (std::regex_search(ctl_file_path_, sm, expression)) {
            int count = sm.size();
            string time_string = sm[1];

            generateTimeForGrapes(time_string.substr(0, 10), time_string.substr(10, 3));
            return;
        }
    }
}

void GradsCtlParser::generateTimeForGrapes(
        const std::string &start_hour_string,
        const std::string &forecast_hour_string)
{
    auto year = boost::lexical_cast<int>(start_hour_string.substr(0, 4));
    auto month = boost::lexical_cast<int>(start_hour_string.substr(4, 2));
    auto day = boost::lexical_cast<int>(start_hour_string.substr(6, 2));
    auto hour = boost::lexical_cast<int>(start_hour_string.substr(8));
    grads_ctl_.start_time_ = boost::posix_time::ptime(
            boost::gregorian::date(year, month, day),
            boost::posix_time::time_duration(hour, 0, 0)
    );

    auto forecast_hour = boost::lexical_cast<int>(forecast_hour_string);
    grads_ctl_.forecast_time_ = boost::posix_time::hours(forecast_hour);
}
