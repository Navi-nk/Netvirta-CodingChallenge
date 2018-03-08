#include <gtest/gtest.h>
#include "search_executor.hpp"

struct input_mock
{
    std::vector<std::string> inputStr;
    int matrixSize;
    bool success;
};

class SearchExecutorTest : public testing::Test,
                           public testing::WithParamInterface<input_mock>
{
  public:
    SearchExecutor *searchExecutor;

    void SetUp()
    {
        searchExecutor = new SearchExecutor;
    }
    void TearDown()
    {
        delete searchExecutor;
    }
};

TEST_P(SearchExecutorTest, ShouldPreprocessInputMatrix)
{
    auto input = GetParam();
    EXPECT_EQ(input.success, searchExecutor->preprocess(input.inputStr));
    
    MatrixData matrixData = searchExecutor->getMatrixData();

    EXPECT_EQ(input.matrixSize, matrixData.matrix.size());

    if(input.success)
    {
        EXPECT_EQ(0,matrixData.matrixMap[matrixData.matrix[0][0]][0][0]);
        EXPECT_EQ(1,matrixData.matrixMap[matrixData.matrix[0][0]][1][0]);
    }
        
}

INSTANTIATE_TEST_CASE_P(Default, SearchExecutorTest,
                        testing::Values(
                            input_mock{
                                {{"10,2,-12"}, {"3,10,5"}, {"7,-411,71"}},
                                3,
                                true},
                            input_mock{
                                {{"1,2,f"}, {"3,5,2"}, {"7,r,7"}},
                                0,
                                false},
                            input_mock{
                                {},
                                0,
                                false}));

