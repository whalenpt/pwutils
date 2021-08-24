
#include "pwutils/report/basereport.h"
#include "pwutils/report/reporthelper.h"
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>

namespace pw{

void ReportBase::internalFileHandle(std::ofstream& os) const
{
    pw::createDirectory(m_dirpath,false);
    os.open(pw::filePath(m_dirpath,m_name,m_extension));
    if(!os.is_open())
        throw std::runtime_error("Failed to open data file for output stream");
    report(os);
    os.close();
}

std::ofstream& operator<<(std::ofstream& os,const ReportBase& def){
    // If ofstream os is not open, try to open and output
    if(!os.is_open())
        def.internalFileHandle(os);
    else
        def.report(os);
    return os;
}

std::ofstream& operator<<(std::ofstream& os,const ReportBase* def){ 
    if(!os.is_open())
        def->internalFileHandle(os);
    else
        def->report(os);
    return os;
}

std::ofstream& operator<<(std::ofstream& os,const std::unique_ptr<ReportBase> def)
{ 
    if(!os.is_open())
        def->internalFileHandle(os);
    else
        def->report(os);
    return os;
}

void ReportBase::setItem(const std::string& key,double val) {
    std::string strVal = std::to_string(val);
    m_metadata_map[key] = strVal;
}

void ReportBase::setItem(const std::string& key,const std::string& nm) {
  m_metadata_map[key] = nm;
}

void ReportBase::removeItem(const std::string& key) {
  m_metadata_map.erase(key);
}

void ReportBase::setFileSignature(FileSignature file_sig) {
    m_metadata_map["FileSignature"] = std::to_string(static_cast<int>(file_sig));
}

void ReportBase::setDataSignature(DataSignature data_sig){
    m_metadata_map["DataSignature"] = std::to_string(static_cast<int>(data_sig));
}
void ReportBase::setOperatorSignature(OperatorSignature op_sig) {
    m_metadata_map["OperatorSignature"] = std::to_string(static_cast<int>(op_sig));
}

FileSignature ReportBase::fileSignature() const
{
    const auto it = m_metadata_map.find("FileSignature");
    if(it != m_metadata_map.end())
        return static_cast<FileSignature>(std::stoi(it->second));
    return FileSignature::UNKNOWN;
}

DataSignature ReportBase::dataSignature() const
{
    const auto it = m_metadata_map.find("DataSignature");
    if(it != m_metadata_map.end())
        return static_cast<DataSignature>(std::stoi(it->second));
    return DataSignature::UNKNOWN;
}

OperatorSignature ReportBase::operatorSignature() const
{
    const auto it = m_metadata_map.find("OperatorSignature");
    if(it != m_metadata_map.end())
        return static_cast<OperatorSignature>(std::stoi(it->second));
    return OperatorSignature::NONE;
}


}

