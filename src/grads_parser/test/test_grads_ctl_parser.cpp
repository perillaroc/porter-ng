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

    TEST_F(GradsCtlParser, MethodInit) {
        const string test_ctl_file_path = "src/grads_parser/test/test_data/post.ctl_2018011912_000";
        GradsParser::GradsCtlParser parser;
        parser.parse(test_ctl_file_path);
        GradsParser::GradsCtl grads_ctl = parser.grads_ctl_;


        EXPECT_EQ(grads_ctl.data_file_path_, "src/grads_parser/test/test_data/postvar2018011912_000");
        EXPECT_EQ(grads_ctl.title_, "post output from grapes");
        EXPECT_DOUBLE_EQ(grads_ctl.undefined_value_, -9999.0);

        EXPECT_EQ(grads_ctl.x_def_.count_, 1440);
        EXPECT_EQ(grads_ctl.x_def_.type_, GradsParser::DimensionType::Linear);

        EXPECT_EQ(grads_ctl.y_def_.count_, 720);
        EXPECT_EQ(grads_ctl.y_def_.type_, GradsParser::DimensionType::Linear);

        EXPECT_EQ(grads_ctl.z_def_.count_, 29);
        EXPECT_EQ(grads_ctl.z_def_.type_, GradsParser::DimensionType::Level);


    }

    TEST_F(GradsCtlParser, MethodHelloWorld) {
        EXPECT_EQ(0, 0);
    }

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}