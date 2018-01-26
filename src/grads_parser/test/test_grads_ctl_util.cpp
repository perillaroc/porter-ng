#include <gtest/gtest.h>

#include "grads_ctl_util.h"
#include "grads_ctl_parser.h"

using namespace std;

namespace {

    class GradsCtlUtilTest : public ::testing::Test {
    protected:

        GradsCtlUtilTest() {
        }

        virtual ~GradsCtlUtilTest() {
        }


        virtual void SetUp() {
            test_ctl_file_path_ = "src/grads_parser/test/test_data/post.ctl_2018011912_000";
        }

        virtual void TearDown() {
        }

        string test_ctl_file_path_;
    };

    TEST_F(GradsCtlUtilTest, MethodParse) {
        GradsParser::GradsCtlParser parser;
        parser.parse(test_ctl_file_path_);
        auto grads_ctl = parser.getGradsCtl();

        int index = -1;

        index = GradsParser::GradsUtil::findVariableIndex(
                grads_ctl, "u", GradsParser::LevelType::Multi, 1000.0
        );
        EXPECT_EQ(index, 0);


        index = GradsParser::GradsUtil::findVariableIndex(
                grads_ctl, "u", GradsParser::LevelType::Multi, 962.5
        );
        EXPECT_EQ(index, 1);


        index = GradsParser::GradsUtil::findVariableIndex(
                grads_ctl, "v", GradsParser::LevelType::Multi, 1000.0
        );
        EXPECT_EQ(index, 29);


        index = GradsParser::GradsUtil::findVariableIndex(
                grads_ctl, "ps", GradsParser::LevelType::Single, 0.0
        );
        EXPECT_EQ(index, 356);

    }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}