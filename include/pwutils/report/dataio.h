
#ifndef DATAIO_H_
#define DATAIO_H_

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "pwutils/pwexcept.h"

namespace pw{

namespace fs = std::filesystem;

fs::path createDirectory(const std::string& dir_name, bool overwrite = true);
void createDirectory(const std::filesystem::path& dir_path,bool overwrite = true);
void clearDirectory(const std::filesystem::path& dir_path);

fs::path filePath(const fs::path& dir_path,\
        const std::string& nm,int repNum,const std::string& extension); 
fs::path filePath(const fs::path& dir_path,\
        const std::string& nm,const std::string& extension);

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
        static const int PRECISION = 16;
        static const int WIDTH = 24;
};

template<typename T>
void DataIO::writeFile(const fs::path& fname,const std::vector<T>& x) const
{
    fs::path file_path = m_dirpath / fname;
    std::ofstream fout(file_path);
    for(int j = 0; j < x.size(); j++)
        fout << std::scientific << std::setprecision(PRECISION) << std::setw(WIDTH) << x[j] << std::endl;
    fout.close();
}

template<typename T1,typename T2>
void DataIO::writeFile(const fs::path& fname,const std::vector<T1>& x,const std::vector<T2>& y) const
{
    assert(x.size() == y.size());
    fs::path file_path = m_dirpath / fname;
    std::ofstream fout(file_path);
    for(int j = 0; j < x.size(); j++){
        fout << std::scientific << std::setprecision(PRECISION) << std::setw(WIDTH) << x[j] 
           << std::scientific << std::setprecision(PRECISION) << std::setw(WIDTH) << y[j] << std::endl; 
    }
    fout.close();
}






}

#endif

