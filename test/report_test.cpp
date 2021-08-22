
#include <gtest/gtest.h>
#include <pwutils/report/dat.hpp>
#include <pwutils/report/json.hpp>

TEST(REPORT_TEST,REPORT_DAT){
    int N = 20;
    std::vector<int> int_vec(N,0);
    std::vector<double> double_vec(N,1.);
    std::vector<double> second_dvec(N,2.);

    dat::ReportData1D<int,double> data1("test1.json",int_vec,double_vec);
    data1.setReportMetadata(false);
    std::filesystem::path path1 = data1.path(std::filesystem::temp_directory_path());
    std::ofstream os{path1};
    os << data1;
    os.close();
    EXPECT_TRUE(std::filesystem::exists(path1));

    dat::ReportData1D<double,double> data2("double_vector",double_vec,second_dvec);
    data2.setReportMetadata(false);
    std::filesystem::path path2 = data2.path(std::filesystem::temp_directory_path());
    os.open(path2);
    os << data2;
    os.close();
    EXPECT_TRUE(std::filesystem::exists(path2));

    dat::TrackData<double> track_max("double_vector",pw::TrackType::Max,double_vec);
    std::filesystem::path path3 = track_max.path(std::filesystem::temp_directory_path());
    os.open(path3);
    os << track_max;
    os.close();
    EXPECT_TRUE(std::filesystem::exists(path3));
}

TEST(REPORT_TEST,REPORT_JSON){
    int N = 20;
    std::vector<int> int_vec(N,0);
    std::vector<double> double_vec(N,1.);
    std::vector<double> second_dvec(N,2.);

    json::ReportData1D<int,double> data1("test1.json",int_vec,double_vec);
    data1.setReportMetadata(false);
    std::filesystem::path path1 = data1.path(std::filesystem::temp_directory_path());
    std::ofstream os(path1);
    os << std::fixed << std::setprecision(4);
    os << data1;
    os.close();
    EXPECT_TRUE(std::filesystem::exists(path1));

    json::ReportData1D<double,double> data2("double_vector",double_vec,second_dvec);

    data2.setReportMetadata(false);
    std::filesystem::path path2 = data2.path(std::filesystem::temp_directory_path());
    std::ofstream os2(path2);
    os2 << std::scientific << std::setprecision(4);
    os2.open(data2.path(path2));
    os2 << data2;
    os2.close();
//    std::cout << path2 << std::endl;
//    std::ifstream infile{path2};
//
//    while(!infile.eof()){
//        double a,b;
//        infile >> a >> b;
//        std::cout << a << " - " << b << std::endl;
//    }

    EXPECT_TRUE(std::filesystem::exists(path2));


//    json::TrackData<double> track_max("double_vector",pw::TrackType::Max,double_vec);
//    os.open(track_max.filePath(std::filesystem::temp_directory_path()));
//    os << track_max;
//    os.close();

}


TEST(REPORT_TEST,REPORT_DAT_2D){
    int N1 = 10;
    int N2 = 20;
    std::vector<int> x(N1,0);
    std::vector<double> y(N2,5.0);
    std::vector<double> z(N1*N2,1.0);

    dat::ReportData2D<int,double,double> data1("dat2D.dat",x,y,z);
    data1.setReportMetadata(false);
    std::filesystem::path path1 = data1.path(std::filesystem::temp_directory_path());
    std::ofstream os{path1};
    os << data1;
    os.close();
    EXPECT_TRUE(std::filesystem::exists(path1));

    std::ifstream infile{path1};
    int nx,ny;
    infile >> nx >> ny;
    EXPECT_EQ(nx,N1);
    EXPECT_EQ(ny,N2);
    std::vector<int> xin(nx);
    std::vector<double> yin(ny);
    std::vector<double> zin(nx*ny);
    for(auto i = 0; i < nx; i++)
        infile >> xin[i];
    for(auto j = 0; j < ny; j++)
        infile >> yin[j];
    std::string line;
    int i = 0;
    while(std::getline(infile,line)){
	std::stringstream ss(line);
	double val;
        while(ss >> val){ 
	    zin[i] = val;
            i++;
	}
    }
    EXPECT_EQ(z.size(),zin.size());
    EXPECT_DOUBLE_EQ(z[10],1.0);
}








