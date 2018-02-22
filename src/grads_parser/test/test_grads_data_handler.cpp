#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include "test_config.h"
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
            test_ctl_file_path_ = string(TEST_DATA_ROOT) + "/sample/meso_postvar_sample.ctl";
        }

        virtual void TearDown()
        {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }

        // Objects declared here can be used by all tests in the test case for Foo.
        string test_ctl_file_path_;
    };

    TEST_F(GradsDataHandlerTest, MethodLoadByIndex)
    {
        GradsParser::GradsCtlParser parser;
        parser.parse(test_ctl_file_path_);
        auto grads_ctl = parser.getGradsCtl();
        grads_ctl.data_endian_ = GradsParser::DataEndian::BigEndian;

        GradsParser::GradsDataHandler handler{grads_ctl};
        handler.openDataFile();

        int index = 3;
        auto record_handler = handler.loadByIndex(index);

        auto variable = record_handler->variable();
        EXPECT_EQ(variable.name_, "h");
        EXPECT_DOUBLE_EQ(variable.level_, 1000.0);

        index=1;
        record_handler = handler.loadByIndex(index);

        variable = record_handler->variable();
        EXPECT_EQ(variable.name_, "t");
        EXPECT_DOUBLE_EQ(variable.level_, 975.0);

        // non-exists index
        index=6000;
        record_handler = handler.loadByIndex(index);

        EXPECT_EQ(record_handler.get(), nullptr);
    }

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}