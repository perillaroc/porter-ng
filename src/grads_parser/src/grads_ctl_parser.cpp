#include "grads_ctl_parser.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include <fstream>

#include <iostream>

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
        string cur_line = ctl_file_lines_[cur_line_no_];
        vector<string> tokens;
        alg::split(tokens, cur_line, alg::is_space(), boost::token_compress_on);
        if(!tokens.empty())
        {
            string first_word = tokens[0];
            cout<<first_word<<endl;
            if(first_word == "dset")
            {
                parseDset(tokens);
            }
            else if(first_word == "title")
            {
                string title = alg::trim_copy(cur_line);
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
        }
        cur_line_no_++;
    }
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
            string cur_line = ctl_file_lines_[cur_line_no_];
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
