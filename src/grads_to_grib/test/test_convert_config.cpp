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

        EXPECT_EQ(param_configs.size(), 5);

        ParamConfig u_config = param_configs[0];
        EXPECT_EQ(u_config.name_, "u");
        EXPECT_EQ(u_config.number_keys_.at("discipline"), 0);
        EXPECT_EQ(u_config.number_keys_.at("parameterCategory"), 2);
        EXPECT_EQ(u_config.number_keys_.at("parameterNumber"), 2);

        EXPECT_EQ(u_config.string_keys_.at("typeOfLevel"), "isobaricInPa");

        EXPECT_FALSE(u_config.isLevelSet());

        ParamConfig v_config = param_configs[1];
        EXPECT_EQ(v_config.name_, "v");
        EXPECT_EQ(v_config.number_keys_.at("discipline"), 0);
        EXPECT_EQ(v_config.number_keys_.at("parameterCategory"), 2);
        EXPECT_EQ(v_config.number_keys_.at("parameterNumber"), 3);

        EXPECT_EQ(v_config.string_keys_.at("typeOfLevel"), "isobaricInPa");

        EXPECT_FALSE(v_config.isLevelSet());

        ParamConfig tsoil_config = param_configs[4];
        EXPECT_EQ(tsoil_config.name_, "tsoil");

        vector<double> tsoil_expected_levels = {1000.0};
        EXPECT_EQ(tsoil_config.levels_, tsoil_expected_levels);

        EXPECT_EQ(tsoil_config.number_keys_.at("discipline"), 0);
        EXPECT_EQ(tsoil_config.number_keys_.at("parameterCategory"), 0);
        EXPECT_EQ(tsoil_config.number_keys_.at("parameterNumber"), 0);
        EXPECT_EQ(tsoil_config.number_keys_.at("typeOfFirstFixedSurface"), 106);
        EXPECT_EQ(tsoil_config.number_keys_.at("scaleFactorOfFirstFixedSurface"), 2);
        EXPECT_EQ(tsoil_config.number_keys_.at("scaledValueOfFirstFixedSurface"), 0);
        EXPECT_EQ(tsoil_config.number_keys_.at("typeOfSecondFixedSurface"), 106);
        EXPECT_EQ(tsoil_config.number_keys_.at("scaleFactorOfSecondFixedSurface"), 2);
        EXPECT_EQ(tsoil_config.number_keys_.at("scaledValueOfSecondFixedSurface"), 10);

        EXPECT_TRUE(tsoil_config.isLevelSet());

        auto props_config = convert_config.gradsCtlPropsConfig();
        EXPECT_EQ(props_config.size(), 3);
        EXPECT_NE(props_config.find("start_time"), props_config.end());
        EXPECT_EQ(props_config["start_time"], "2018021200");
        EXPECT_NE(props_config.find("forecast_time"), props_config.end());
        EXPECT_EQ(props_config["forecast_time"], "000");
        EXPECT_NE(props_config.find("data_endian"), props_config.end());
        EXPECT_EQ(props_config["data_endian"], "big_endian");

        EXPECT_EQ(props_config.find("NONE_KEY"), props_config.end());
    }

    TEST_F(ConvertConfigTest, MethodFindParamConfig)
    {
        string config_file_path = "src/grads_to_grib/test/data/grapes_gfs_postvar.config.yaml";
        ConvertConfig convert_config;
        convert_config.parse(config_file_path);

        auto case1 = convert_config.findParamConfig("u");
        EXPECT_NE(case1, end(convert_config.paramConfigs()));
        auto case1_param_config = *case1;
        EXPECT_EQ(case1_param_config.number_keys_["discipline"], 0);
        EXPECT_EQ(case1_param_config.number_keys_["parameterCategory"], 2);
        EXPECT_EQ(case1_param_config.number_keys_["parameterNumber"], 2);
        EXPECT_EQ(case1_param_config.string_keys_["typeOfLevel"], "isobaricInPa");

        auto case2 = convert_config.findParamConfig("error_param_name");
        EXPECT_EQ(case2, end(convert_config.paramConfigs()));

    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}