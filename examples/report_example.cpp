
#include <vector>
#include <fstream>
#include <iostream>
#include <pwutils/report/dat.h>

int main()
{
    int N = 20;
    std::vector<pw::dcmplx> cplx_vec(N,0.);
    dat::ReportComplexVector report_def("complex_vector",cplx_vec);
    report_def.setReportMetadata(false);
    report_def.setPrecision(3);
    std::ofstream os(report_def.filePath("outfolder").string());
    os << report_def;
    os.close();

    std::vector<double> double_vec(N,1.0);
    dat::ReportRealVector report_real("real_vector",double_vec);
    report_real.setReportMetadata(false);
    report_real.setPrecision(3);
    os.open(report_real.filePath("outfolder").string());
    report_real.report(os);
    os.close();

    std::vector<pw::dcmplx> cplx_vec2(N,0.);
    dat::ReportComplexVector complex_def("complex_vector2",cplx_vec2);
    complex_def.setReportMetadata(false);
    complex_def.setPrecision(3);
    os.open(complex_def.filePath("outfolder").string());
    os << complex_def;
    os.close();

    pw::DataIO dataio("outfolder");
    dataio.writeFile("double_vec.dat",double_vec);
    std::vector<double> double_vec2(N,5.0);
    dataio.writeFile("two_double_vecs.dat",double_vec,double_vec2);
    std::vector<int> int_vec(10,1);
    dataio.writeFile("int_vec.dat",int_vec);
    dataio.writeFile("complex_vec.dat",cplx_vec);

    return 0;

}







