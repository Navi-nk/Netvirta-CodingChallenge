#include <gtest/gtest.h>
#include "unordered_search.hpp"
#include "search_executor.hpp"
#include <gmock/gmock.h>
#include <algorithm>

struct unordered_mock
{
    lvec inputArr;
    lvec outputArr;
};

class UnorderedSearchTest : public testing::Test,
                            public testing::WithParamInterface<unordered_mock>
{
  public:
    SearchExecutor *searchExecutor;

    UnorderedSearchTest()
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
        searchExecutor->setSearchStrategy("searchUnordered");
    }
    void TearDown()
    {
        delete searchExecutor;
    }
};

TEST_P(UnorderedSearchTest, ShouldPreformUnOrderedSearch)
{
    auto input = GetParam();
    lvec out = searchExecutor->performSearch(input.inputArr);
    std::sort(out.begin(), out.end());
    EXPECT_THAT(input.outputArr, out);
}

INSTANTIATE_TEST_CASE_P(Default, UnorderedSearchTest,
                        testing::Values(
                            unordered_mock{
                                {891, 53, 90, 141},
                                {0, 3}},
                            unordered_mock{
                                {62653, -2621, -6290},
                                {4}},
                            unordered_mock{
                                {},
                                {-1}},
                            unordered_mock{
                                {24, 260, 62, -156, 62, 732, 854, 67, 116},
                                {2}},
                            unordered_mock{
                                {-361,102,9730,891,14731,563,223,-3,-36},
                                {5}},
                            unordered_mock{
                                {102, -361, 891, 563, 9730, 1473, -3, -36, 223},
                                {-1}},
                            unordered_mock{
                                {24, 260, 62, -156, 62, 732, 854, 67, 116, 0},
                                {-1}}));
