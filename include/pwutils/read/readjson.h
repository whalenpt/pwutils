
#ifndef READJSON_H_
#define READJSON_H_ 

#include <fstream>
#include <vector>
#include <string>
#include "pwutils/pwdefs.h"
#include "pwutils/pwconstants.h"

namespace json11{
    class Json;
}

namespace json{
    pw::metadataMap getMetaData(std::ifstream& iss);
    pw::metadataMap getMetaData(const std::filesystem::path& path);
    pw::DataSignature dataSignature(const std::filesystem::path& path);
    pw::DataSignature deduceDataSignature(std::ifstream& fin);
    void readJSONstring(const std::filesystem::path& path,std::string& str);
    void readJsonObject(const std::filesystem::path& path,json11::Json& json_obj);
    void readXdata(const json11::Json& json_obj,std::vector<double>& x);
    void readYdata(const json11::Json& json_obj,std::vector<double>& y);

    pw::OperatorSignature operatorSignature(const std::filesystem::path& path);
    pw::metadataMap readXY(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y);
    pw::metadataMap readXY_C(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<pw::dcmplx>& y);
    pw::metadataMap readXY_C(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y,std::vector<double>& z);
}

#endif


