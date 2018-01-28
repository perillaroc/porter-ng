#pragma once

#include "grads_ctl.h"

namespace GradsParser {

    class GradsCtlParser {
    public:
        GradsCtlParser();

        void parse(const std::string &ctl_file_path);

        GradsCtl& getGradsCtl() { return grads_ctl_; }

    private:
        void loadCtlFileLines();

        void parseDataSet(std::vector<std::string> &tokens);

        void parseDimension(std::string dimension_name, std::vector<std::string> &tokens);

        void parseTimeDimension(std::vector<std::string> &tokens);

        void parseVariableRecords(std::vector<std::string> &tokens);

        void parseFileName();

        void generateVariableList();

        void generateTimeForGrapes(const std::string &start_hour_string, const std::string &forecast_hour_string);

        std::string ctl_file_path_;

        GradsCtl grads_ctl_;
        std::vector<std::string> ctl_file_lines_;
        int cur_line_no_;
    };

}


