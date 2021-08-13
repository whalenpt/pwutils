
#ifndef READFILE_H_
#define READFILE_H_ 

#include <fstream>
#include <string>
#include <vector>

namespace pw{
    enum class DataFileSignature{DAT,JSON,UNKNOWN};
    DataFileSignature deduceDataFileType(const std::string& name);
    DataFileSignature deduceDataFileSignature(std::ifstream& fin);
    void openFile(const std::string& fname,std::ifstream& fin);
    DataFileSignature checkJSONSignature(std::ifstream& fin,std::string& line);
    DataFileSignature checkDatSignature(std::ifstream& fin,std::vector<std::string>& line_data);
    bool checkJSONline(std::string& line);
    void getDatLineData(std::ifstream& infile,std::vector<std::string>& line_data);
}


#endif
