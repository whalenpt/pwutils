
#ifndef READFILE_H_
#define READFILE_H_ 

#include <fstream>
#include <string>

#include "pwutils/report/reporthelper.h"

namespace pw{
    enum class DataFileSignature{DAT,JSON,UNKNOWN};
    DataFileSignatue deduceDataFileType(const std::string& name);
    DataFileSignatue deduceDataFileSignature(std::ifstream& fin);
    void openFile(const std::string& fname,std::ifstream& fin);
    DataFileSignatue checkJSONSignature(std::ifstream& fin,std::string& line);
    DataFileSignatue checkDatSignature(std::ifstream& fin,std::vector<std::string>& line_data);
    bool checkJSONline(std::string& line);
    void getDatLineData(std::ifstream& infile,std::vector<std::string>& line_data);
}
