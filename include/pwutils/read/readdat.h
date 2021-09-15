// readdat.h
#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "pwutils/pwdefs.h"
#include "pwutils/pwconstants.h"

namespace dat{
    using pw::dcmplx;
    pw::DataSignature dataSignature(const std::filesystem::path& path);
    pw::DataSignature deduceDataSignature(std::ifstream& fin);

    pw::OperatorSignature operatorSignature(const std::filesystem::path& path);
    pw::metadataMap getHeaderContent(std::ifstream& iss);
    void getLineOfData(std::ifstream& fin,std::vector<std::string>& line_data);
    pw::metadataMap readXY(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y);
    pw::metadataMap readXCVY(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<dcmplx>& y);
    pw::metadataMap readXCVY(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& yreal,std::vector<double>& yimag);
    pw::metadataMap readXYZ(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y,std::vector<double>& z);
    pw::metadataMap readXYCVZ(const std::filesystem::path& path,std::vector<double>& x,
            std::vector<double>& y,std::vector<dcmplx>& z);
    void readXY3D(std::ifstream& fin,std::vector<double>& x,std::vector<double>& y);
}



