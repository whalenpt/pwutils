
#include <gtest/gtest.h>
#include <filesystem>
#include <pwutils/pwdefs.h>
#include <pwutils/read/readdat.h>
#include <pwutils/read/readjson.h>
#include <pwutils/read/readfile.h>


TEST(READ_JSON_TEST,EXTENSION_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/T_0.json"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::JSON);
}

TEST(READ_JSON_TEST,SIGNATURE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/T_0_sig.txt"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::JSON);
}

TEST(READ_JSON_TEST,INFERENCE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/T_0.txt"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::JSON);
}

TEST(READ_DAT_TEST,EXTENSION_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0.dat"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::DAT);
}

TEST(READ_DAT_TEST,SIGNATURE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0_sig.txt"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::DAT);
}

TEST(READ_DAT_TEST,INFERENCE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0.txt"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::DAT);
}




