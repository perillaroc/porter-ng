#include <iostream>

#include <grads_to_grib_converter.h>

using namespace std;
using namespace GradsToGrib;

int main(int argc, char *argv[])
{
    if(argc < 4)
    {
        cout<<"Usage: simple_grads2grib config_file_path ctl_file_path output_file_path"<<endl;
        return 1;
    }
    string config_file_path{argv[1]};
    string ctl_file_path{argv[2]};
    string output_file_path{argv[3]};

    GradsToGribConverter converter;
    converter.setConvertConfigFilePath(config_file_path);
    converter.setCtlFilePath(ctl_file_path);
    converter.setOutputFilePath(output_file_path);

    converter.convert();

    return 0;
}
