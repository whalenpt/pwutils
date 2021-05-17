
#include <vector>
#include <fstream>
#include <iostream>
#include <pwutils/report/dat.h>

int main()
{
    int N = 20;
    std::vector<pw::dcmplx> cplx_vec(N,0.);
    std::unique_ptr<dat::ReportComplexVector> report_def(\
        new dat::ReportComplexVector("complex_vector",cplx_vec));
    report_def->setReportMetadata(false);
    report_def->setPrecision(3);
    std::ofstream os(report_def->filePath().string());
    os << report_def.get();
    os.close();

    std::vector<double> double_vec(N,1.0);
    std::unique_ptr<dat::ReportRealVector> report_real(\
        new dat::ReportRealVector("real_vector",double_vec));
    report_real->setReportMetadata(false);
    report_real->setPrecision(3);
    os.open(report_real->filePath().string());
    report_real->report(os);
    os.close();

    std::vector<pw::dcmplx> cplx_vec2(N,0.);
    std::unique_ptr<dat::ReportComplexVector> complex_def(\
        new dat::ReportComplexVector("complex_vector2",cplx_vec2));
    complex_def->setReportMetadata(false);
    complex_def->setPrecision(3);
    os.open(complex_def->filePath().string());
    // Need to dereference unique_ptr
    os << *complex_def;
    os.close();
    return 0;

}







