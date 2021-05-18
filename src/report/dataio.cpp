
#include "pwutils/report/reporthelper.h"
#include "pwutils/report/dataio.h"
#include "pwutils/pwexcept.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <cassert>

namespace pw{

fs::path createDirectory(const std::string& dir_name, bool overwrite)
{
    fs::path dir_path = fs::current_path() / dir_name;
    createDirectory(dir_path,overwrite);
    return dir_path;
}

void createDirectory(const std::filesystem::path& dir_path,bool overwrite)
{
	if(overwrite)
	    clearDirectory(dir_path);
	if(!fs::exists(dir_path)){
        fs::create_directory(dir_path);
	}
}

void clearDirectory(const std::filesystem::path& dir_path)
{
	if(fs::exists(dir_path)){
        fs::remove_all(dir_path);
	}
}

fs::path filePath(const fs::path& dir_path,
		const std::string& nm,int repNum,const std::string& extension) 
{
	fs::path local_path(nm+"_"+std::to_string(repNum)+"." + extension);
	fs::path full_path = dir_path / local_path;
	return full_path;
}

fs::path filePath(const fs::path& dir_path,
		const std::string& nm,const std::string& extension) 
{
	fs::path local_path(nm+"."+extension);
	fs::path full_path = dir_path / local_path;
	return full_path;
}

DataIO::DataIO(const fs::path& dir_path) : m_dirpath(dir_path)
{
    createDirectory(m_dirpath,false);
}

void DataIO::setDirectoryPath(const fs::path& dirpath)
{
    if(fs::is_directory(dirpath)){
       m_dirpath = dirpath;
    } else{
        std::string str("DataIO::DataIO(std::filesystem::path& path) \
             specified directory path IS NOT a directory path ");
        throw pw::Exception(str);
    }
}




}







