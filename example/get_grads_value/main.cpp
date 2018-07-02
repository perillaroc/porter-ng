#include <iostream>
#include <algorithm>
#include <memory>

#include <grads_ctl_parser.h>
#include <grads_ctl_util.h>
#include <grads_data_handler.h>

using namespace std;
using namespace GradsParser;

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cout<<"Usage: get_grads_value ctl_file_path"<<endl;
        return 1;
    }
    string ctl_file_path{argv[1]};

    GradsCtlParser parser;
    parser.parse(ctl_file_path);
    auto grads_ctl = parser.getGradsCtl();
    grads_ctl.data_endian_ = DataEndian::BigEndian;

    string var_name = "u";
    double level = 962.5;
    auto index = GradsUtil::findVariableIndex(grads_ctl, var_name, LevelType::Multi, level);
	std::cout << "index=" << index << std::endl;

    return 0;
}
