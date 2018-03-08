#include <gtest/gtest.h>
#include <enc_dec_file.hpp>
#include <fstream>
#include <cstdio>

class EncDecTest : public testing::Test
{
    public:
        EncDecHelper encDecHelper;
        std::string testString;

    void SetUp()
    {
        testString = "This is test string";

        std::ofstream outfile ("../data/test_data.csv");
        outfile << testString << std::endl;
        outfile.close();
    }
    void TearDown()
    {
        std::remove("../data/test_data.csv");
        std::remove("../data/enc-test_data.csv");
    }

};

TEST_F(EncDecTest, ShouldEncryptDecryptString)
{
    std::string encryptedStr = encDecHelper.encryptDecrypt(testString);
    std::string decryptedStr = encDecHelper.encryptDecrypt(encryptedStr);

    EXPECT_EQ(testString, decryptedStr);
}

TEST_F(EncDecTest, ShouldEncryptDecryptFile)
{
    std::string filePath = "../data";
    std::string fileName="test_data.csv";

    EXPECT_EQ(true, encDecHelper.encryptFile(filePath,fileName));

    std::vector<std::string> out = encDecHelper.decryptFile("../data/enc-test_data.csv");
    EXPECT_EQ(out[0], testString);
}
