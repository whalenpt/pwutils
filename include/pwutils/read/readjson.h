
#ifndef READJSON_H_
#define READJSON_H_ 

#include <fstream>
#include <vector>
#include <string>
#include "pwutils/pwdefs.h"

namespace json{
//    pw::metadataMap getHeaderContent(std::ifstream& iss);
//    pw::DataSignature deduceDataSignature(std::ifstream& fin);
    pw::DataSignature dataSignature(const std::filesystem::path& path);
//    pw::DataSignature deduceDataSignature(std::ifstream& fin);
    pw::OperatorSignature operatorSignature(const std::filesystem::path& path);
//    void getLineOfData(std::ifstream& fin,std::vector<std::string>& line_data);
}

#endif


