#include "grads_ctl_util.h"

using namespace GradsParser;

int GradsUtil::findVariableIndex(
        const GradsCtl &grads_ctl,
        const std::string &variable_name,
        LevelType level_type,
        double level)
{
    auto vars = grads_ctl.vars_;
    auto count = grads_ctl.vars_.size();
    int index = -1;
    for(auto i=0; i<count; i++)
    {
        auto var = grads_ctl.vars_[i];
        if(var.name_ == variable_name
           && var.level_type_ == level_type
           && var.level_ == level)
        {
            index = i;
            break;
        }
    }
    return index;
}
