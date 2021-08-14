
#ifndef READJSON_H_
#define READJSON_H_ 

#include <fstream>
#include <vector>
#include <string>
#include "pwutils/pwdefs.h"
#include "pwutils/pwconstants.h"

namespace json{
//    pw::metadataMap getHeaderContent(std::ifstream& iss);
//    pw::DataSignature deduceDataSignature(std::ifstream& fin);
    pw::DataSignature dataSignature(const std::filesystem::path& path);
//    pw::DataSignature deduceDataSignature(std::ifstream& fin);
    pw::OperatorSignature operatorSignature(const std::filesystem::path& path);
//    void getLineOfData(std::ifstream& fin,std::vector<std::string>& line_data);
    pw::metadataMap readXY(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y);
    pw::metadataMap readXY_C(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<pw::dcmplx>& y);
    pw::metadataMap readXY_C(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y,std::vector<double>& z);

}

#endif


