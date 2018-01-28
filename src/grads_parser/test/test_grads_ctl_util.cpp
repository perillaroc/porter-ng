#include <gtest/gtest.h>

#include "grads_ctl_util.h"
#include "grads_ctl_parser.h"

using namespace std;

namespace {

    class GradsCtlUtilTest : public ::testing::Test {
    protected:

        GradsCtlUtilTest()
        {
            test_ctl_file_path_ = "src/grads_parser/test/test_data/post.ctl_2018011912_000";
        }

        virtual ~GradsCtlUtilTest() {}


        virtual void SetUp() {}

        virtual void TearDown() {}

        string test_ctl_file_path_;
    };

    TEST_F(GradsCtlUtilTest, FindVariableIndex) {
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

        // non-exists variable
        index = GradsParser::GradsUtil::findVariableIndex(
                grads_ctl, "t", GradsParser::LevelType::Single, 1000.0
        );
        EXPECT_EQ(index, -1);

        index = GradsParser::GradsUtil::findVariableIndex(
                grads_ctl, "no", GradsParser::LevelType::Multi, 1000.0
        );
        EXPECT_EQ(index, -1);

        index = GradsParser::GradsUtil::findVariableIndex(
                grads_ctl, "t", GradsParser::LevelType::Multi, 951.0
        );
        EXPECT_EQ(index, -1);

    }

    TEST_F(GradsCtlUtilTest, RearrangeValueMatrix)
    {
        size_t x_count;
        size_t y_count;

        double x_step;
        double y_step;

        vector<float> case1 = {
                1,  2,  3,  4,
                5,  6,  7,  8,
                9, 10, 11, 12
        };
        vector<float> case1_expected_result = {
                9, 10, 11, 12,
                5,  6,  7,  8,
                1,  2,  3,  4
        };
        x_count = 4;
        y_count = 3;
        x_step = 1;
        y_step = 4;

        auto case1_result = GradsParser::GradsUtil::rearrangeValueMatrix(case1, x_count, y_count, x_step, y_step);
        EXPECT_EQ(case1_result, case1_expected_result);

        vector<float> case2 = {
                9, 10, 11, 12,
                5,  6,  7,  8,
                1,  2,  3,  4
        };
        vector<float> case2_expected_result = {
                9, 10, 11, 12,
                5,  6,  7,  8,
                1,  2,  3,  4
        };
        x_count = 4;
        y_count = 3;
        x_step = 1;
        y_step = -4;
        auto case2_result = GradsParser::GradsUtil::rearrangeValueMatrix(case2, x_count, y_count, x_step, y_step);
        EXPECT_EQ(case2_result, case2_expected_result);

    }

    TEST_F(GradsCtlUtilTest, FormatDateTime)
    {
        boost::posix_time::ptime time{boost::gregorian::date{2018, 1, 28},
                                      boost::posix_time::time_duration{8, 12, 3}};
        string time_string =  GradsParser::GradsUtil::formatDateTime(time, "%Y%m%d");
        EXPECT_EQ(time_string, "20180128");
    }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}