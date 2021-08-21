
#include <vector>
#include <fstream>
#include <iostream>
#include <pwutils/report/dat.hpp>
#include <pwutils/report/json.hpp>
#include <pwutils/report/dataio.hpp>

int main()
{
    int N = 20;

    // Use pw::DataIO for simple vector data file reporting
    pw::DataIO dataio("outfolder");
    std::vector<int> int_vec(N,1);

    dataio.writeFile("int_vec.dat",int_vec);
    std::vector<double> double_vec(N,1.);
    dataio.writeFile("double_vec.dat",double_vec);
    std::vector<pw::dcmplx> cplx_vec(N,0.);
    dataio.writeFile("complex_vec.dat",cplx_vec);
    std::vector<double> double_vec2(N,5.0);
    dataio.writeFile("two_double_vecs.dat",double_vec,double_vec2);

    // Use ReportData1D for data reporting with x, and y vector variables
    dat::ReportData1D<int,double> data1D("double_data",int_vec,double_vec);
    data1D.setReportMetadata(false);
    data1D.setPrecision(3);
    std::ofstream os(data1D.filePath("outfolder").string());
    os << data1D;
    os.close();

    // Use ReportComplexData1D for data reporting with x, and y when y is complex
    dat::ReportComplexData1D<int> report_def("complex_data",int_vec,cplx_vec);
    report_def.setReportMetadata(false);
    report_def.setPrecision(3);
    os.open(report_def.filePath("outfolder").string());
    os << report_def;
    os.close();

    // Report doubles
    dat::ReportData1D<double,double> report_real("real_data",double_vec,double_vec);
    report_real.setReportMetadata(false);
    report_real.setPrecision(3);
    os.open(report_real.filePath("outfolder").string());
    report_real.report(os);
    os.close();

    // Json
    json::ReportData1D<int,double> jdata1D("double_data.json",int_vec,double_vec);
    jdata1D.setReportMetadata(false);
    jdata1D.setPrecision(3);
    os.open(jdata1D.filePath("outfolder").string());
    os << jdata1D;
    os.close();

    // Use ReportComplexData1D for data reporting with x, and y when y is complex
    json::ReportComplexData1D<int> jreport_def("complex_data",int_vec,cplx_vec);
    jreport_def.setReportMetadata(false);
    jreport_def.setPrecision(3);
    os.open(jreport_def.filePath("outfolder").string());
    os << jreport_def;
    os.close();

    // Report doubles
    json::ReportData1D<double,double> jreport_real("real_data",double_vec,double_vec);
    jreport_real.setReportMetadata(false);
    jreport_real.setPrecision(3);
    os.open(jreport_real.filePath("outfolder").string());
    jreport_real.report(os);
    os.close();

    // Report 2D 
    int nx = 10;
    int ny = 20;
    std::vector<double> x(nx,1.);
    std::vector<double> y(ny,4.);
    std::vector<double> z(nx*ny,0.0);

    dat::ReportData2D<double,double,double> rp_2D("XY2D",x,y,z);
    rp_2D.setReportMetadata(false);
    rp_2D.setPrecision(3);
    os.open(rp_2D.filePath("outfolder").string());
    rp_2D.report(os);
    os.close();

    // Report 2D complex
    std::vector<dat::dcmplx> z2(nx*ny,dat::dcmplx(1.0,2.0));
    dat::ReportComplexData2D<double,double> rp_2DC("XY2DC",x,y,z2);
    rp_2DC.setPrecision(3);
    os.open(rp_2DC.filePath("outfolder").string());
    rp_2DC.report(os);

    os.close();

    return 0;

}







