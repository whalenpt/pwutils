
#include <vector>
#include <fstream>
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
    os << report_def;
    os.close();
    return 0;
}







