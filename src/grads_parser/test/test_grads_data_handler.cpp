#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include "grads_ctl_parser.h"
#include "grads_data_handler.h"

using namespace std;

namespace {

// The fixture for testing class Foo.
    class GradsDataHandlerTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        GradsDataHandlerTest()
        {
            // You can do set-up work for each test here.
        }

        virtual ~GradsDataHandlerTest()
        {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        virtual void SetUp()
        {
            // Code here will be called immediately after the constructor (right
            // before each test).
            test_ctl_file_path_ = "dist/data/post.ctl_2018012400_000";
        }

        virtual void TearDown()
        {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }

        // Objects declared here can be used by all tests in the test case for Foo.
        string test_ctl_file_path_;
    };

    TEST_F(GradsDataHandlerTest, MethodLoadData)
    {
        GradsParser::GradsCtlParser parser;
        parser.parse(test_ctl_file_path_);
        GradsParser::GradsCtl grads_ctl = parser.getGradsCtl();
        grads_ctl.data_endian_ = GradsParser::DataEndian::BigEndian;

        GradsParser::GradsDataHandler handler{grads_ctl};
        handler.openDataFile();

        int current_index = 1;
        while(handler.hasNext())
        {
            cout<<"Loading variable "<<current_index<<"/"<<grads_ctl.vars_.size()<<endl;
            vector<float> values = handler.loadNext();
            EXPECT_EQ(values.size(), 1036800);
            current_index++;
        }
    }

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}