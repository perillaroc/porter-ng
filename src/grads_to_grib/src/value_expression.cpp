#include "value_expression.h"

#include <algorithm>

using namespace GradsToGrib;

ValueExpression::ValueExpression(const std::string &expr) {
    setExpression(expr);
}

void ValueExpression::setExpression(const std::string &expr) {
    expression_string_ = expr;
    expression_parser_.SetExpr(expression_string_);
}

void ValueExpression::applyToArray(std::vector<double>::iterator source_begin,
                                   std::vector<double>::iterator source_end,
                                   std::vector<double>::iterator target_begin) {
    double value = 0.0;
    expression_parser_.DefineVar("x", &value);
    std::transform(source_begin, source_end, target_begin,
                   [&](double v){
                       value = v;
                       double result = expression_parser_.Eval();
                       return result;
                   });

}
