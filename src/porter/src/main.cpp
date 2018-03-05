#include <grads_converter.h>

#include <iostream>
#include <boost/program_options.hpp>
#include <cxxopts.hpp>

using namespace std;
using namespace GradsConvert;

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    cxxopts::Options options("porter", "A data converter.");
    options.positional_help("[ctl file path list]").show_positional_help();

    options.add_options()
            ("h,help", "Print help")
            ("c,config", "config file path", cxxopts::value<string>())
            ("o,output", "output file path", cxxopts::value<string>())
            ("ctl_file_path", "ctl file paths", cxxopts::value<vector<string>>());

    options.parse_positional({"ctl_file_path"});

    auto result = options.parse(argc, argv);

    if (result.count("help")){
        std::cout << options.help({""}) << std::endl;
        exit(0);
    }

    string config_file_path{result["config"].as<string>()};
    string output_file_path{result["output"].as<string>()};
    vector<string> ctl_file_list{result["ctl_file_path"].as<vector<string>>()};

    for(auto &ctl_file_path: ctl_file_list)
    {
        GradsConverter converter;
        converter.setConfigFilePath(config_file_path);
        converter.setCtlFilePath(ctl_file_path);
        converter.setOutputFilePath(output_file_path);

        converter.convert();
    }

    return 0;
}
