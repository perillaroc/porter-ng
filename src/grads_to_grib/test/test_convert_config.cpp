#include <gtest/gtest.h>

#include <convert_config.h>

using namespace std;
using namespace GradsToGrib;

namespace {

    class ConvertConfigTest : public ::testing::Test {
    protected:

        ConvertConfigTest()
        {
        }

        virtual ~ConvertConfigTest() {}


        virtual void SetUp() {}

        virtual void TearDown() {}
    };

    TEST_F(ConvertConfigTest, MethodParse)
    {
        string config_file_path = "src/grads_to_grib/test/data/grapes_gfs_postvar.config.yaml";
        ConvertConfig convert_config;
        convert_config.parse(config_file_path);

        vector<ParamConfig> param_configs = convert_config.paramConfigs();

        EXPECT_EQ(param_configs.size(), 3);

        ParamConfig u_config = param_configs[0];
        EXPECT_EQ(u_config.name_, "u");
        EXPECT_EQ(u_config.number_keys_.at("discipline"), 0);
        EXPECT_EQ(u_config.number_keys_.at("parameterCategory"), 2);
        EXPECT_EQ(u_config.number_keys_.at("parameterNumber"), 2);

        EXPECT_EQ(u_config.string_keys_.at("typeOfLevel"), "isobaricInPa");

        ParamConfig v_config = param_configs[1];
        EXPECT_EQ(v_config.name_, "v");
        EXPECT_EQ(v_config.number_keys_.at("discipline"), 0);
        EXPECT_EQ(v_config.number_keys_.at("parameterCategory"), 2);
        EXPECT_EQ(v_config.number_keys_.at("parameterNumber"), 3);

        EXPECT_EQ(v_config.string_keys_.at("typeOfLevel"), "isobaricInPa");
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}