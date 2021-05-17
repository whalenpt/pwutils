
#include "pwutils/report/reportdata.h"
#include "pwutils/report/reporthelper.h"
#include <filesystem>

namespace pw{

std::filesystem::path filePath(const std::filesystem::path& dir_path,
		const std::string& nm,int repNum,const std::string& extension) 
{
	std::filesystem::path local_path(nm+"_"+std::to_string(repNum)+"." + extension);
	std::filesystem::path full_path = dir_path / local_path;
	return full_path;
}

std::filesystem::path filePath(const std::filesystem::path& dir_path,
		const std::string& nm,const std::string& extension) 
{
	std::filesystem::path local_path(nm+"."+extension);
	std::filesystem::path full_path = dir_path / local_path;
	return full_path;
}

std::filesystem::path filePath(const std::string& nm,int repNum,const std::string& extension)
{
    std::filesystem::path dir_path(CURRENT_DIR_PATH);
    dir_path /= DEFAULT_REPORTOUT_DIR; 
    if(!std::filesystem::is_directory(dir_path))
        std::filesystem::create_directory(dir_path);
	std::filesystem::path local_path(nm+"_"+std::to_string(repNum)+"." + extension);
	return dir_path / local_path;
}

std::filesystem::path filePath(const std::string& nm,const std::string& extension)
{
    std::filesystem::path dir_path(CURRENT_DIR_PATH);
    dir_path /= DEFAULT_REPORTOUT_DIR; 
    if(!std::filesystem::is_directory(dir_path))
        std::filesystem::create_directory(dir_path);
	std::filesystem::path local_path(nm+"."+extension);
	return dir_path / local_path;
}

void VBReport::setItem(const std::string& key,double val) {
    std::string strVal = std::to_string(val);
    m_metadata_map.erase(key);
    m_metadata_map.insert(pw::metadataPair(key,strVal));
}

void VBReport::addItem(const std::string& ky,const std::string& nm)
{
  m_metadata_map.insert(pw::metadataPair(ky,nm));
}

void VBReport::addItem(const std::string& ky,double val)
{
  std::string nm = std::to_string(val);
  m_metadata_map.insert(pw::metadataPair(ky,nm));
}

void VBReport::removeItem(const std::string& ky)
{
  m_metadata_map.erase(ky);
}


}

