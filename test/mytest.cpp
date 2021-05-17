
#include <gtest/gtest.h>
#include <pwutils/pwstrings.h>
#include <pwutils/report/dat.h>
#include <string>

TEST(PWUTILS_TESTS,STRINGS) {
    std::string str("UPPER and lower CaSes");
	EXPECT_EQ(pw::stringLowerCase(str),"upper and lower cases"); 
	EXPECT_EQ(pw::stringUpperCase(str),"UPPER AND LOWER CASES"); 
}

TEST(PWUTILS_TESTS,REPORTING){
    int N = 20;
    std::vector<pw::dcmplx> cplx_vec(N,0.);
    std::unique_ptr<dat::ReportComplexVector> report_def(\
        new dat::ReportComplexVector("complex_vector",cplx_vec));
    report_def->setReportMetadata(false);
    report_def->setPrecision(3);
    std::ofstream os(report_def->filePath().string());
    os << report_def;
    os.close();
    EXPECT_TRUE(true);
}







