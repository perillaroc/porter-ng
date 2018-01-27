#include "grads_ctl_util.h"

using namespace GradsParser;
using namespace std;

int GradsUtil::findVariableIndex(
        const GradsCtl &grads_ctl,
        const string &variable_name,
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

vector<float> GradsUtil::rearrangeValueMatrix(
        const vector<float> &input_values, size_t x_count, size_t y_count, double x_step, double y_step)
{
    vector<float> values(input_values.size());

    if(x_step > 0 && y_step > 0)
    {
        // rearrange
        for(auto y=0; y<y_count; y++)
        {
            for(auto x=0; x<x_count; x++)
            {
                values[x_count*(y_count-1-y) + x] = input_values[x_count*y + x];
            }
        }
    }
    else
    {
        copy(input_values.begin(), input_values.end(), values.begin());
    }

    return values;
}

string GradsUtil::formatDateTime(const boost::posix_time::ptime &time, const string &time_format)
{
    static std::locale loc(
            cout.getloc(),
            new boost::posix_time::time_facet(time_format.c_str()));

    ostringstream ss;
    ss.imbue(loc);
    ss << time;
    return ss.str();
}
