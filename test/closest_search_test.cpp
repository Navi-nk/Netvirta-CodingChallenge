#include <gtest/gtest.h>
#include "closest_search.hpp"
#include "search_executor.hpp"
#include <gmock/gmock.h>
#include <algorithm>

struct closest_mock
{
    lvec inputArr;
    lvec outputArr;
};

class ClosestSearchTest : public testing::Test,
                          public testing::WithParamInterface<closest_mock>
{
  public:
    SearchExecutor *searchExecutor;

    ClosestSearchTest()
    {
        searchExecutor = new SearchExecutor;
        searchExecutor->preprocess({{"10,-1,891,53,90,141,5,67,22"},
                                    {"2,-1,23,53,100,141,5,67,-100"},
                                    {"24,260,62,-156,62,732,854,67,116"},
                                    {"1560,-631,891,53,90,141,465,-267,-6222"},
                                    {"10,-1,891,62653,-6290,-2621,65,667,282"},
                                    {"102,-361,891,563,9730,14731,-3,-36,223"}});
    }
    void SetUp()
    {
        searchExecutor->setSearchStrategy("searchClosest");
    }
    void TearDown()
    {
        delete searchExecutor;
    }
};

TEST_P(ClosestSearchTest, ShouldPerformClosestSearch)
{
    auto input = GetParam();
    lvec out = searchExecutor->performSearch(input.inputArr); 
    std::sort(out.begin(),out.end());
    EXPECT_EQ(input.outputArr, out);
}

INSTANTIATE_TEST_CASE_P(Default, ClosestSearchTest,
                        testing::Values(
                            closest_mock{
                                {891, 53, 90, 141},
                                {0, 3}},
                            closest_mock{
                                {62653, -6290, -2621},
                                {4}},
                            closest_mock{
                                {},
                                {-1}},
                            closest_mock{
                                {24, 260, 62, -156, 62, 732, 854, 67, 116},
                                {2}},
                            closest_mock{
                                {102, -361, 891, 563, 9730, 1473, -3, -36, 223},
                                {5}},
                            closest_mock{
                                {24, 260, 62, -156, 62, 732, 854, 67, 116, 0},
                                {2}}));
