#include <iostream>
#include <boost/program_options.hpp>

#include <grads_to_grib_converter.h>

using namespace std;
using namespace GradsToGrib;

namespace po = boost::program_options;

int main(int argc, const char *argv[])
{
    po::options_description desc{"Options"};
    desc.add_options()
            ("help,h", "Show this help")
            ("config,c", po::value<string>(), "config file path")
            ("output,o", po::value<string>(), "output file path")
            ("ctl-file-path", po::value<vector<string>>(), "ctl file paths");

    po::positional_options_description pos_desc;
    pos_desc.add("ctl-file-path", 1);

    po::command_line_parser parser{argc, argv};
    parser.options(desc).positional(pos_desc).allow_unregistered();
    po::parsed_options parsed_options = parser.run();

    po::variables_map vm;
    po::store(parsed_options, vm);
    po::notify(vm);

    if(vm.count("help") ){
        std::cout << desc << std::endl;
        return 0;
    }

    string config_file_path{vm["config"].as<string>()};
    string output_file_path{vm["output"].as<string>()};
    vector<string> ctl_file_list{vm["ctl-file-path"].as<vector<string>>()};

    for(auto &ctl_file_path: ctl_file_list)
    {
        GradsToGribConverter converter;
        converter.setConvertConfigFilePath(config_file_path);
        converter.setCtlFilePath(ctl_file_path);
        converter.setOutputFilePath(output_file_path);

        converter.convert();
    }

    return 0;
}
