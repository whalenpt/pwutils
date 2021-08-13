
#ifndef READFILE_H_
#define READFILE_H_ 

#include <fstream>
#include <string>
#include <vector>
#include "pwutils/pwdefs.h"

namespace pw{
    FileSignature deduceDataFileType(const std::string& name);
    FileSignature deduceFileSignature(std::ifstream& fin);
    void openFile(const std::string& fname,std::ifstream& fin);
    FileSignature checkJSONSignature(std::ifstream& fin,std::string& line);
    FileSignature checkDatSignature(std::ifstream& fin,std::vector<std::string>& line_data);
    bool checkJSONline(std::string& line);
    void getDatLineData(std::ifstream& infile,std::vector<std::string>& line_data);
}

#endif



