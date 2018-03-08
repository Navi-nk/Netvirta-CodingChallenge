#include <gtest/gtest.h>
#include "ordered_search.hpp"
#include "search_executor.hpp"
#include <gmock/gmock.h>

struct ordered_mock
{
    lvec inputArr;
    lvec outputArr;
};

class OrderedSearchTest : public testing::Test,
                          public testing::WithParamInterface<ordered_mock>
{
  public:
    SearchExecutor *searchExecutor;

    OrderedSearchTest()
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
        searchExecutor->setSearchStrategy("searchOrdered");
    }
    void TearDown()
    {
        delete searchExecutor;
    }
};

TEST_P(OrderedSearchTest, ShouldPreformOrderedSearch)
{
    auto input = GetParam();

    EXPECT_THAT(input.outputArr, testing::Each(searchExecutor->performSearch(input.inputArr)));
}

INSTANTIATE_TEST_CASE_P(Default, OrderedSearchTest,
                        testing::Values(
                            ordered_mock{
                                {891, 53, 90, 141},
                                {0, 3}},
                            ordered_mock{
                                {62653, -6290, -2621},
                                {4}},
                            ordered_mock{
                                {},
                                {-1}},
                            ordered_mock{
                                {24, 260, 62, -156, 62, 732, 854, 67, 116},
                                {2}},
                            ordered_mock{
                                {102, -361, 891, 563, 9730, 1473, -3, -36, 223},
                                {-1}},
                            ordered_mock{
                                {24, 260, 62, -156, 62, 732, 854, 67, 116, 0},
                                {-1}}));
