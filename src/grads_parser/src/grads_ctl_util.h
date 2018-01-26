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
    }
}
