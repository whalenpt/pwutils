// readjson.h
#pragma once 

#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "pwutils/pwdefs.h"
#include "pwutils/pwconstants.h"

namespace json11{
    class Json;
}

namespace json{
    using pw::dcmplx;
    pw::metadataMap getMetaData(std::ifstream& iss);
    pw::metadataMap getMetaData(const std::filesystem::path& path);
    pw::DataSignature dataSignature(const std::filesystem::path& path);
    pw::DataSignature deduceDataSignature(std::ifstream& fin);
    void readJSONstring(const std::filesystem::path& path,std::string& str);
    void readJsonObject(const std::filesystem::path& path,json11::Json& json_obj);
    void readVecData(const json11::Json& json_obj,std::vector<double>& vec,\
            const std::string& id,std::string id_label="");
    pw::OperatorSignature operatorSignature(const std::filesystem::path& path);
    pw::metadataMap readXY(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y);
    pw::metadataMap readXCVY(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<dcmplx>& y);
    pw::metadataMap readXCVY(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y,std::vector<double>& z);
    pw::metadataMap readXYZ(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y,std::vector<double>& z);
    pw::metadataMap readXYCVZ(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y,std::vector<dcmplx>& z);
}


