#pragma once

#include "grads_ctl.h"

namespace GradsParser {

    class GradsCtlParser {
    public:
        GradsCtlParser();

        void parse(const std::string &ctl_file_path);

        GradsCtl getGradsCtl() const
        {
            return grads_ctl_;
        }

    private:

        void parseDset(std::vector<std::string> &tokens);

        void parseDimension(std::string dimension_name, std::vector<std::string> &tokens);

        void parseTimeDimension(std::vector<std::string> &tokens);

        void parseVariableDefs(std::vector<std::string> &tokens);

        void generateVariableList();

        std::string ctl_file_path_;

        GradsCtl grads_ctl_;
        std::vector<std::string> ctl_file_lines_;
        int cur_line_no_;
    };

}


