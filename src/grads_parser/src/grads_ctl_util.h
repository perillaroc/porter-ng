#pragma once

#include "grads_ctl.h"

namespace GradsParser
{
    namespace GradsUtil
    {
        int findVariableIndex(
                const GradsCtl &grads_ctl,
                const std::string &variable_name,
                LevelType level_type,
                double level
        );

        std::vector<float> rearrangeValueMatrix(
                const std::vector<float> &input_values, size_t x_count, size_t y_count, double x_step, double y_step);

        std::string formatDateTime(const boost::posix_time::ptime &time, const std::string &time_format);
    }
}
