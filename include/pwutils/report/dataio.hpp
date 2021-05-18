
#ifndef DATAIO_HPP_
#define DATAIO_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "pwutils/report/reporthelper.h"

namespace pw{

namespace fs = std::filesystem;

class DataIO{
    public:
        DataIO(const fs::path& dirpath = fs::current_path());
        void setDirectoryPath(const fs::path& dirpath);
        template<typename T>
        void writeFile(const fs::path& fname,const std::vector<T>& x) const;
        template<typename T1,typename T2>
        void writeFile(const fs::path& fname,const std::vector<T1>& x,const std::vector<T2>& y) const;
        void clearDirectory() { pw::clearDirectory(m_dirpath); }
    private:
        fs::path m_dirpath;
};

template<typename T>
void DataIO::writeFile(const fs::path& fname,const std::vector<T>& x) const
{
    fs::path file_path = m_dirpath / fname;
    std::ofstream fout(file_path);
    for(int j = 0; j < x.size(); j++)
        fout << std::scientific << std::setprecision(pw::REPORT_PRECISION) 
             << std::setw(pw::REPORT_PRECISION + pw::REPORT_PADING) << x[j] << std::endl;
    fout.close();
}

template<typename T1,typename T2>
void DataIO::writeFile(const fs::path& fname,const std::vector<T1>& x,const std::vector<T2>& y) const
{
    assert(x.size() == y.size());
    fs::path file_path = m_dirpath / fname;
    std::ofstream fout(file_path);
    for(int j = 0; j < x.size(); j++){
        fout << std::scientific << std::setprecision(pw::REPORT_PRECISION) 
            << std::setw(pw::REPORT_PRECISION + pw::REPORT_PADING) << x[j] 
            << std::scientific << std::setprecision(pw::REPORT_PRECISION) 
            << std::setw(pw::REPORT_PRECISION + pw::REPORT_PADING) << y[j] << std::endl; 
    }
    fout.close();
}






}

#endif

