#include "grads_ctl_parser.h"

using namespace GradsParser;
using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout<<"Usage: "<<argv[0]<<" ctl_file_path";
        return 1;
    }

    string ctl_file_path(argv[1]);

    GradsCtlParser parser;
    parser.parse(ctl_file_path);

    GradsCtl grads_ctl = parser.getGradsCtl();

//    for(const auto &line: parser.ctl_file_lines_)
//    {
//        cout<<line<<endl;
//    }

    return 0;
}