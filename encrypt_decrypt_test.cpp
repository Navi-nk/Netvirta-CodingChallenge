#include <gtest/gtest.h>
#include <enc_dec_file.hpp>

TEST(EncDecTest, ShouldEncryptDecryptString)
{
    EncDecHelper encDecHelper;
    std::string testStr = "This is test string";
    
    std::string encryptedStr = encDecHelper.encryptDecrypt(testStr);
    std::string decryptedStr = encDecHelper.encryptDecrypt(encryptedStr);

    EXPECT_EQ(testStr,decryptedStr);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();   
}