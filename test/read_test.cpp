
#include <gtest/gtest.h>
#include <filesystem>
#include <pwutils/pwdefs.h>
#include <pwutils/read/readdat.h>
#include <pwutils/read/readjson.h>
#include <pwutils/read/readfile.h>


TEST(READ_JSON_TEST,FILE_EXTENSION_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/T_0.json"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::JSON);
}

TEST(READ_JSON_TEST,FILE_SIGNATURE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/T_0_sig.txt"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::JSON);
}

TEST(READ_JSON_TEST,FILE_INFERENCE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/T_0.txt"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::JSON);
}

TEST(READ_DAT_TEST,FILE_EXTENSION_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0.dat"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::DAT);
}

TEST(READ_DAT_TEST,FILE_SIGNATURE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0_sig.txt"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::DAT);
}

TEST(READ_DAT_TEST,FILE_INFERENCE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0.txt"));
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::DAT);
}


TEST(READ_JSON_TEST,DATA_XY_INFERENCE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/T_0.json"));
    pw::DataSignature data_sig = pw::dataSignature(input,pw::FileSignature::JSON);
    EXPECT_EQ(data_sig,pw::DataSignature::XY);
}

TEST(READ_JSON_TEST,DATA_XY_SIGNATURE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/T_0_sig.txt"));
    pw::DataSignature data_sig = pw::dataSignature(input,pw::FileSignature::JSON);
    EXPECT_EQ(data_sig,pw::DataSignature::XY);
}

TEST(READ_DAT_TEST,DATA_XY_INFERENCE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0.dat"));
    pw::DataSignature data_sig = pw::dataSignature(input,pw::FileSignature::DAT);
    EXPECT_EQ(data_sig,pw::DataSignature::XY);
}

TEST(READ_DAT_TEST,DATA_XY_SIGNATURE_TEST){
    std::filesystem::path input(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0_sig.txt"));
    pw::DataSignature data_sig = pw::dataSignature(input,pw::FileSignature::DAT);
    EXPECT_EQ(data_sig,pw::DataSignature::XY);
}



