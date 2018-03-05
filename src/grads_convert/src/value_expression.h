#pragma once
#include <string>
#include <vector>

#include <muParser.h>

namespace GradsConvert {

class ValueExpression {
public:
    ValueExpression() = default;
    explicit ValueExpression(const std::string &expr);

    void setExpression(const std::string &expr);

    void applyToArray(std::vector<double>::iterator source_begin,
                      std::vector<double>::iterator source_end,
                      std::vector<double>::iterator target_begin);

private:
    std::string expression_string_;
    mu::Parser expression_parser_;
};

};

