
#ifndef PWDEFS_H_ 
#define PWDEFS_H_

#include <map>

namespace pw{
    using metadataMap = std::map<std::string,std::string>;
    using metadataPair = std::pair<std::string,std::string>;
    enum class FileSignature{DAT,JSON,UNKNOWN};
    enum class DataType{XY,XYcomplex,XYZ,XYZcomplex,Unknown};
}

#endif

