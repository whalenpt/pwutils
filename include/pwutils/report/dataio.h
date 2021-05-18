
#ifndef DATAIO_H_
#define DATAIO_H_

#include <vector>
#include <string>
#include <filesystem>

namespace pw{

std::filesystem::path createDirectory(const std::string& dir_name);
std::filesystem::path filePath(const std::filesystem::path& dir_path,\
        const std::string& nm,int repNum,const std::string& extension); 
std::filesystem::path filePath(const std::filesystem::path& dir_path,\
        const std::string& nm,const std::string& extension);
std::filesystem::path filePath(const std::string& nm,int repNum,const std::string& extension);
std::filesystem::path filePath(const std::string& nm,const std::string& extension);

}

#endif

