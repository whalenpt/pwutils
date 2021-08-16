
#include <gtest/gtest.h>
#include <filesystem>
#include <pwutils/pwdefs.h>
#include <pwutils/read/readdat.h>
#include <pwutils/read/readjson.h>
#include <pwutils/read/readfile.h>

TEST(READ_JSON_TEST,FILE_EXTENSION_TEST){
    std::filesystem::path input("data/T_0.json");
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::JSON);
}

TEST(READ_JSON_TEST,FILE_SIGNATURE_TEST){
    std::filesystem::path input("data/T_0_sig.txt");
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::JSON);
}

TEST(READ_JSON_TEST,FILE_INFERENCE_TEST){
    std::filesystem::path input("data/T_0.txt");
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::JSON);
}

TEST(READ_DAT_TEST,FILE_EXTENSION_TEST){
    std::filesystem::path input("data/SQ_T_0.dat");
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::DAT);
}

TEST(READ_DAT_TEST,FILE_SIGNATURE_TEST){
    std::filesystem::path input("data/SQ_T_0_sig.txt");
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::DAT);
}

TEST(READ_DAT_TEST,FILE_INFERENCE_TEST){
    std::filesystem::path input("data/SQ_T_0.txt");
    pw::FileSignature file_sig = pw::fileSignature(input);
    EXPECT_EQ(file_sig,pw::FileSignature::DAT);
}


TEST(READ_JSON_TEST,DATA_XY_INFERENCE_TEST){
    std::filesystem::path input("data/T_0.json");
    pw::DataSignature data_sig = pw::dataSignature(input,pw::FileSignature::JSON);
    EXPECT_EQ(data_sig,pw::DataSignature::XY);
}

TEST(READ_JSON_TEST,DATA_XY_SIGNATURE_TEST){
    std::filesystem::path input("data/T_0_sig.txt");
    pw::DataSignature data_sig = pw::dataSignature(input,pw::FileSignature::JSON);
    EXPECT_EQ(data_sig,pw::DataSignature::XY);
}

TEST(READ_DAT_TEST,DATA_XY_INFERENCE_TEST){
    std::filesystem::path input("data/SQ_T_0.dat");
    pw::DataSignature data_sig = pw::dataSignature(input,pw::FileSignature::DAT);
    EXPECT_EQ(data_sig,pw::DataSignature::XY);
}

TEST(READ_DAT_TEST,DATA_XY_SIGNATURE_TEST){
    std::filesystem::path input("data/SQ_T_0_sig.txt");
    pw::DataSignature data_sig = pw::dataSignature(input,pw::FileSignature::DAT);
    EXPECT_EQ(data_sig,pw::DataSignature::XY);
}

TEST(READ_JSON_TEST,XY_READ_TEST){
    std::filesystem::path input("data/T_0.json");
    std::vector<double> x;
    std::vector<double> y;
    json::readXY(input,x,y);
	EXPECT_NEAR(x.front(),-4e-14,1e-12);
	EXPECT_NEAR(x[1],-3.9843444227005873e-14,1e-12);
	EXPECT_NEAR(x.back(),4e-14,1e-12);
	EXPECT_NEAR(y.front(),5.2898010358161471e+01,1e-12);
	EXPECT_NEAR(y[1],5.2685011178082547e+01,1e-12);
	EXPECT_NEAR(y.back(),5.2898010255919104e+01,1e-12);
}






