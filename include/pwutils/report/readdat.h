
#ifndef READDAT_H_
#define READDAT_H_ 

#include <map>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include "pwutils/report/reporthelper.h"

namespace dat{
    pw::metadataMap getHeaderContent(std::ifstream& iss);
    pw::DataType deduceDataType(std::ifstream& fin);
    pw::DataType dataSignature(std::ifstream& fin);
    void getLineOfData(std::ifstream& fin,std::vector<std::string>& line_data);
}

#endif


