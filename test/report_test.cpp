
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
    data1.setPrecision(3);
    std::filesystem::path path1 = data1.filePath(std::filesystem::temp_directory_path());
    std::ofstream os{path1};
    os << data1;
    os.close();
    EXPECT_TRUE(std::filesystem::exists(path1));

    dat::ReportData1D<double,double> data2("double_vector",double_vec,second_dvec);
    data2.setReportMetadata(false);
    data2.setPrecision(3);
    std::filesystem::path path2 = data2.filePath(std::filesystem::temp_directory_path());
    os.open(path2);
    os << data2;
    os.close();
    EXPECT_TRUE(std::filesystem::exists(path2));

    dat::TrackData<double> track_max("double_vector",pw::TrackType::Max,double_vec);
    std::filesystem::path path3 = track_max.filePath(std::filesystem::temp_directory_path());
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
    data1.setPrecision(3);
    std::filesystem::path path1 = data1.filePath(std::filesystem::temp_directory_path());
    std::ofstream os(path1);
    os << data1;
    os.close();
    EXPECT_TRUE(std::filesystem::exists(path1));

    json::ReportData1D<double,double> data2("double_vector",double_vec,second_dvec);
    data2.setReportMetadata(false);
    data2.setPrecision(3);
    std::filesystem::path path2 = data2.filePath(std::filesystem::temp_directory_path());
    os.open(data2.filePath(path2));
    os << data2;
    os.close();
    EXPECT_TRUE(std::filesystem::exists(path2));

//    json::TrackData<double> track_max("double_vector",pw::TrackType::Max,double_vec);
//    os.open(track_max.filePath(std::filesystem::temp_directory_path()));
//    os << track_max;
//    os.close();

}









