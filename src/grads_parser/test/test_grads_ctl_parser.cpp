#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include "grads_ctl_parser.h"

#include "test_config.h"

using namespace std;

namespace {

// The fixture for testing class Foo.
    class GradsCtlParser : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        GradsCtlParser() {
            postvar_ctl_file_path_ = string(TEST_DATA_ROOT) + "/ctl/gfs/post.ctl_2018011912_000";
            modelvar_ctl_file_path_ = string(TEST_DATA_ROOT) + "/ctl/gfs/model.ctl_2018012600_003";
        }

        virtual ~GradsCtlParser() {}

        virtual void SetUp() {}

        virtual void TearDown() {}

        // Objects declared here can be used by all tests in the test case for Foo.
        string postvar_ctl_file_path_;
        string modelvar_ctl_file_path_;
    };

    TEST_F(GradsCtlParser, TestPostVarParse) {
        GradsParser::GradsCtlParser parser;
        parser.parse(postvar_ctl_file_path_);
        auto grads_ctl = parser.getGradsCtl();


        EXPECT_EQ(grads_ctl.data_file_path_, string(TEST_DATA_ROOT) + "/ctl/gfs/postvar2018011912_000");
        EXPECT_EQ(grads_ctl.title_, "post output from grapes");
        EXPECT_DOUBLE_EQ(grads_ctl.undefined_value_, -9999.0);

        // x def
        EXPECT_EQ(grads_ctl.x_def_.count_, 1440);
        EXPECT_DOUBLE_EQ(grads_ctl.x_def_.step_, 0.25);
        EXPECT_EQ(grads_ctl.x_def_.mapping_type_, GradsParser::DimensionMappingType::Linear);
        auto x_level_values = grads_ctl.x_def_.values_;
        double x_level = 0.0;
        double x_step = 0.25;
        for(auto i=0; i<grads_ctl.x_def_.count_; i++)
        {
            EXPECT_DOUBLE_EQ(x_level_values[i], x_level);
            x_level += x_step;
        }

        // y def
        EXPECT_EQ(grads_ctl.y_def_.count_, 720);
        EXPECT_DOUBLE_EQ(grads_ctl.y_def_.step_, 0.25);
        EXPECT_EQ(grads_ctl.y_def_.mapping_type_, GradsParser::DimensionMappingType::Linear);
        auto y_level_values = grads_ctl.y_def_.values_;
        double y_level = -89.875;
        double y_step = 0.25;
        for(auto i=0; i<grads_ctl.y_def_.count_; i++)
        {
            EXPECT_DOUBLE_EQ(y_level_values[i], y_level);
            y_level += y_step;
        }

        // z def
        EXPECT_EQ(grads_ctl.z_def_.count_, 29);
        EXPECT_EQ(grads_ctl.z_def_.mapping_type_, GradsParser::DimensionMappingType::Level);
        auto z_level_values = grads_ctl.z_def_.values_;
        vector<double> z_level_expected_values = {
                1000.000000,
                962.5000000,
                925.0000000,
                887.5000000,
                850.0000000,
                800.0000000,
                750.0000000,
                700.0000000,
                650.0000000,
                600.0000000,
                550.0000000,
                500.0000000,
                450.0000000,
                400.0000000,
                350.0000000,
                300.0000000,
                275.0000000,
                250.0000000,
                225.0000000,
                200.0000000,
                175.0000000,
                150.0000000,
                125.0000000,
                100.0000000,
                70.00000000,
                50.00000000,
                30.00000000,
                20.00000000,
                10.00000000
        };
        for(auto i=0; i<29; i++)
        {
            EXPECT_DOUBLE_EQ(z_level_values[i], z_level_expected_values[i]);
        }

        // t def
        EXPECT_EQ(grads_ctl.t_def_.count_, 1);
        EXPECT_EQ(grads_ctl.t_def_.mapping_type_, GradsParser::DimensionMappingType::Linear);
        auto t_values = grads_ctl.t_def_.values_;
        EXPECT_EQ(t_values.size(), 1);
        EXPECT_EQ(t_values[0], boost::posix_time::ptime(
                boost::gregorian::date(2018, 1, 19),
                boost::posix_time::time_duration(12, 0, 0)
        ));

        // variables
        EXPECT_EQ(grads_ctl.var_records_.size(), 55);
        EXPECT_EQ(grads_ctl.var_infos_.size(), 397);
        auto var = grads_ctl.var_infos_[0];
        EXPECT_EQ(var.name_, "u");
        EXPECT_DOUBLE_EQ(var.level_, 1000.0);
        EXPECT_EQ(var.level_type_, GradsParser::LevelType::Multi);
        EXPECT_EQ(var.level_mapping_type_, GradsParser::DimensionMappingType::Level);
        EXPECT_EQ(var.description_, "u_wind");
        EXPECT_EQ(var.units_, "0");
        EXPECT_EQ(var.time_, boost::posix_time::ptime(
                boost::gregorian::date(2018, 1, 19),
                boost::posix_time::time_duration(12, 0, 0)
        ));

#ifdef PORTER_LITTLE_ENDIAN
        auto local_endian = GradsParser::DataEndian::LittleEndian;
#else
        auto local_endian = GradsParser::DataEndian::BigEndian;
#endif
        EXPECT_EQ(grads_ctl.local_endian_, local_endian);
        EXPECT_EQ(grads_ctl.data_endian_, local_endian);
    }

    TEST_F(GradsCtlParser, TestModelVarParse) {
        GradsParser::GradsCtlParser parser;
        parser.parse(modelvar_ctl_file_path_);
        auto grads_ctl = parser.getGradsCtl();


        EXPECT_EQ(grads_ctl.data_file_path_, string(TEST_DATA_ROOT) + "/ctl/gfs/modelvar2018012600_003");
        EXPECT_EQ(grads_ctl.title_, "model output from grapes");
        EXPECT_DOUBLE_EQ(grads_ctl.undefined_value_, -9.99e33);

        // x def
        EXPECT_EQ(grads_ctl.x_def_.count_, 1440);
        EXPECT_DOUBLE_EQ(grads_ctl.x_def_.step_, 0.25);
        EXPECT_EQ(grads_ctl.x_def_.mapping_type_, GradsParser::DimensionMappingType::Linear);
        auto x_level_values = grads_ctl.x_def_.values_;
        double x_level = 0.0;
        double x_step = 0.25;
        for(auto i=0; i<grads_ctl.x_def_.count_; i++)
        {
            EXPECT_DOUBLE_EQ(x_level_values[i], x_level);
            x_level += x_step;
        }

        // y def
        EXPECT_EQ(grads_ctl.y_def_.count_, 721);
        EXPECT_DOUBLE_EQ(grads_ctl.y_def_.step_, 0.25);
        EXPECT_EQ(grads_ctl.y_def_.mapping_type_, GradsParser::DimensionMappingType::Linear);
        auto y_level_values = grads_ctl.y_def_.values_;
        double y_level = -90;
        double y_step = 0.25;
        for(auto i=0; i<grads_ctl.y_def_.count_; i++)
        {
            EXPECT_DOUBLE_EQ(y_level_values[i], y_level);
            y_level += y_step;
        }

        // z def
        EXPECT_EQ(grads_ctl.z_def_.count_, 62);
        EXPECT_EQ(grads_ctl.z_def_.mapping_type_, GradsParser::DimensionMappingType::Linear);
        EXPECT_EQ(grads_ctl.z_def_.step_, 1);
        auto z_level_values = grads_ctl.z_def_.values_;

        double z_level = 1;
        double z_step = 1;
        for(auto i=0; i<29; i++)
        {
            EXPECT_DOUBLE_EQ(z_level_values[i], z_level);
            z_level += z_step;
        }

        // t def
        EXPECT_EQ(grads_ctl.t_def_.count_, 1);
        EXPECT_EQ(grads_ctl.t_def_.mapping_type_, GradsParser::DimensionMappingType::Linear);
        auto t_values = grads_ctl.t_def_.values_;
        EXPECT_EQ(t_values.size(), 1);
        EXPECT_EQ(t_values[0], boost::posix_time::ptime(
                boost::gregorian::date(2018, 1, 26),
                boost::posix_time::time_duration(3, 0, 0)
        ));

        // variables
        EXPECT_EQ(grads_ctl.var_records_.size(), 57);
        EXPECT_EQ(grads_ctl.var_infos_.size(), 1023);
        auto var = grads_ctl.var_infos_[0];
        EXPECT_EQ(var.name_, "pip");
        EXPECT_DOUBLE_EQ(var.level_, 1);
        EXPECT_EQ(var.level_type_, GradsParser::LevelType::Multi);
        EXPECT_EQ(var.level_mapping_type_, GradsParser::DimensionMappingType::Linear);
        EXPECT_EQ(var.description_, "perturbed PI");
        EXPECT_EQ(var.units_, "99");
        EXPECT_EQ(var.time_, boost::posix_time::ptime(
                boost::gregorian::date(2018, 1, 26),
                boost::posix_time::time_duration(3, 0, 0)
        ));

#ifdef PORTER_LITTLE_ENDIAN
        auto local_endian = GradsParser::DataEndian::LittleEndian;
#else
        auto local_endian = GradsParser::DataEndian::BigEndian;
#endif
        EXPECT_EQ(grads_ctl.local_endian_, local_endian);
        EXPECT_EQ(grads_ctl.data_endian_, local_endian);
    }

    TEST_F(GradsCtlParser, MethodParseFileName)
    {
        GradsParser::GradsCtlParser parser;
        parser.parse(string(TEST_DATA_ROOT) + "/ctl/gfs/post.ctl_2018011912_000");
        auto grads_ctl = parser.getGradsCtl();

        EXPECT_EQ(grads_ctl.forecast_time_, boost::posix_time::hours(0));
        EXPECT_EQ(grads_ctl.start_time_, boost::posix_time::ptime(
                boost::gregorian::date(2018, 1, 19),
                boost::posix_time::time_duration(12, 0, 0)
        ));

        parser.parse(string(TEST_DATA_ROOT) + "/ctl/gfs/model.ctl_2018012600_003");
        grads_ctl = parser.getGradsCtl();

        EXPECT_EQ(grads_ctl.forecast_time_, boost::posix_time::hours(3));
        EXPECT_EQ(grads_ctl.start_time_, boost::posix_time::ptime(
                boost::gregorian::date(2018, 1, 26),
                boost::posix_time::time_duration(0, 0, 0)
        ));
    }

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}