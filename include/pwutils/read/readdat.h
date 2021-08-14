
#ifndef READDAT_H_
#define READDAT_H_ 

#include <fstream>
#include <vector>
#include <string>
#include "pwutils/pwdefs.h"

namespace dat{
    pw::DataSignature dataSignature(const std::filesystem::path& path);
    pw::DataSignature deduceDataSignature(std::ifstream& fin);
    pw::OperatorSignature operatorSignature(const std::filesystem::path& path);
    pw::metadataMap getHeaderContent(std::ifstream& iss);
    void getLineOfData(std::ifstream& fin,std::vector<std::string>& line_data);
}

#endif


