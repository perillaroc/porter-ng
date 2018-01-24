#include <string>
#include <iostream>

#include "gtest/gtest.h"

#include "grads_ctl_parser.h"

using namespace std;

namespace {

// The fixture for testing class Foo.
    class GradsCtlParser : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        GradsCtlParser() {
            // You can do set-up work for each test here.
        }

        virtual ~GradsCtlParser() {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        virtual void SetUp() {
            // Code here will be called immediately after the constructor (right
            // before each test).
        }

        virtual void TearDown() {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }

        // Objects declared here can be used by all tests in the test case for Foo.
    };

    TEST_F(GradsCtlParser, MethodParse) {
        const string test_ctl_file_path = "src/grads_parser/test/test_data/post.ctl_2018011912_000";
        GradsParser::GradsCtlParser parser;
        parser.parse(test_ctl_file_path);
        GradsParser::GradsCtl grads_ctl = parser.grads_ctl_;


        EXPECT_EQ(grads_ctl.data_file_path_, "src/grads_parser/test/test_data/postvar2018011912_000");
        EXPECT_EQ(grads_ctl.title_, "post output from grapes");
        EXPECT_DOUBLE_EQ(grads_ctl.undefined_value_, -9999.0);

        EXPECT_EQ(grads_ctl.x_def_.count_, 1440);
        EXPECT_EQ(grads_ctl.x_def_.type_, GradsParser::DimensionType::Linear);
        auto x_level_values = grads_ctl.x_def_.values_;
        double x_level = 0.0;
        double x_step = 0.25;
        for(auto i=0; i<grads_ctl.x_def_.count_; i++)
        {
            EXPECT_DOUBLE_EQ(x_level_values[i], x_level);
            x_level += x_step;
        }

        EXPECT_EQ(grads_ctl.y_def_.count_, 720);
        EXPECT_EQ(grads_ctl.y_def_.type_, GradsParser::DimensionType::Linear);
        auto y_level_values = grads_ctl.y_def_.values_;
        double y_level = -89.875;
        double y_step = 0.25;
        for(auto i=0; i<grads_ctl.y_def_.count_; i++)
        {
            EXPECT_DOUBLE_EQ(y_level_values[i], y_level);
            y_level += y_step;
        }

        EXPECT_EQ(grads_ctl.z_def_.count_, 29);
        EXPECT_EQ(grads_ctl.z_def_.type_, GradsParser::DimensionType::Level);
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

        EXPECT_EQ(grads_ctl.t_def_.count_, 1);
        EXPECT_EQ(grads_ctl.t_def_.type_, GradsParser::DimensionType::Linear);
        auto t_values = grads_ctl.t_def_.values_;
        EXPECT_EQ(t_values.size(), 1);
        EXPECT_EQ(t_values[0], boost::posix_time::ptime(
                boost::gregorian::date(2018, 1, 19),
                boost::posix_time::time_duration(12, 0, 0)
        ));

        EXPECT_EQ(grads_ctl.var_defs_.size(), 55);

        EXPECT_EQ(grads_ctl.vars_.size(), 397);
    }

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}