
#include <gtest/gtest.h>
#include <pwutils/pwstrings.h>
#include <pwutils/report/dat.hpp>
#include <string>
#include <filesystem>

TEST(PWUTILS_TESTS,STRINGS) {
    std::string str("UPPER and lower CaSes");
	EXPECT_EQ(pw::stringLowerCase(str),"upper and lower cases"); 
	EXPECT_EQ(pw::stringUpperCase(str),"UPPER AND LOWER CASES"); 
}

TEST(PWUTILS_TESTS,REPORT_DAT){
    int N = 20;
//    std::vector<float> x(N,0.);
//    std::vector<pw::dcmplx> cplx_vec(N,0.);
//    dat::ReportComplexData1D<float> report_def("complex_vector",x,cplx_vec);
//    report_def.setReportMetadata(false);
//    report_def.setPrecision(3);
//    std::ofstream os(report_def.filePath(std::filesystem::temp_directory_path()).string());
//    os << report_def;
//    os.close();

    std::vector<int> int_vec(N,0);
    std::vector<double> double_vec(N,1.);
    dat::ReportData1D<int,double> data1D("double_vector",int_vec,double_vec);
    data1D.setReportMetadata(false);
    data1D.setPrecision(3);
    std::ofstream os(data1D.filePath(std::filesystem::temp_directory_path()).string());
    os << data1D;
    os.close();


    EXPECT_TRUE(true);
}







