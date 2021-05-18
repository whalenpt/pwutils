
#include <gtest/gtest.h>
#include <pwutils/pwstrings.h>
#include <pwutils/report/dat.h>
#include <string>
#include <filesystem>

TEST(PWUTILS_TESTS,STRINGS) {
    std::string str("UPPER and lower CaSes");
	EXPECT_EQ(pw::stringLowerCase(str),"upper and lower cases"); 
	EXPECT_EQ(pw::stringUpperCase(str),"UPPER AND LOWER CASES"); 
}

TEST(PWUTILS_TESTS,REPORTING){
    int N = 20;
    std::vector<pw::dcmplx> cplx_vec(N,0.);
    dat::ReportComplexVector report_def("complex_vector",cplx_vec);
    report_def.setReportMetadata(false);
    report_def.setPrecision(3);
    std::ofstream os(report_def.filePath(std::filesystem::temp_directory_path()).string());
    os << report_def;
    os.close();
    EXPECT_TRUE(true);
}







