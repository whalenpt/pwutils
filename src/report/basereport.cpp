
#include "pwutils/report/basereport.h"
#include "pwutils/report/reporthelper.h"
#include <filesystem>

namespace pw{

void ReportBase::setItem(const std::string& key,double val) {
    std::string strVal = std::to_string(val);
    m_metadata_map.erase(key);
    m_metadata_map.insert(pw::metadataPair(key,strVal));
}

void ReportBase::addItem(const std::string& ky,const std::string& nm)
{
  m_metadata_map.insert(pw::metadataPair(ky,nm));
}

void ReportBase::addItem(const std::string& ky,double val)
{
  std::string nm = std::to_string(val);
  m_metadata_map.insert(pw::metadataPair(ky,nm));
}

void ReportBase::removeItem(const std::string& ky)
{
  m_metadata_map.erase(ky);
}


}

