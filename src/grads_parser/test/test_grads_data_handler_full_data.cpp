#include <string>
#include <iostream>
#include <chrono>

#include <gtest/gtest.h>

#include "grads_ctl_parser.h"
#include "grads_data_handler.h"

using namespace std;
using namespace std::chrono;

namespace {

// The fixture for testing class Foo.
    class GradsDataHandlerFullDataTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        GradsDataHandlerFullDataTest()
        {
            // You can do set-up work for each test here.
        }

        virtual ~GradsDataHandlerFullDataTest()
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

    TEST_F(GradsDataHandlerFullDataTest, MethodLoadNext)
    {
        GradsParser::GradsCtlParser parser;
        parser.parse(test_ctl_file_path_);
        auto grads_ctl = parser.getGradsCtl();
        grads_ctl.data_endian_ = GradsParser::DataEndian::BigEndian;

        GradsParser::GradsDataHandler handler{grads_ctl};
        handler.openDataFile();

        int current_index = 1;
        while(handler.hasNext())
        {
            cout<<"Loading variable "<<current_index<<"/"<<grads_ctl.var_infos_.size()<<"...";

            high_resolution_clock::time_point start_time = high_resolution_clock::now();
            auto record_handler = handler.loadNext();
            high_resolution_clock::time_point end_time = high_resolution_clock::now();

            cout<<duration_cast<milliseconds>(end_time-start_time).count()<<" ms"<<endl;

            auto values = record_handler->values();

            EXPECT_EQ(values.size(), 1036800);

            record_handler.reset();

            current_index++;
        }
    }

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}