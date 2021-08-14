
#ifndef PWDEFS_H_ 
#define PWDEFS_H_

#include <map>

namespace pw{
    using metadataMap = std::map<std::string,std::string>;
    using metadataPair = std::pair<std::string,std::string>;
    enum class FileSignature{DAT,JSON,UNKNOWN};
    enum class DataSignature{XY,XY_C,XYZ,XYZ_C,UNKNOWN};
    enum class OperatorSignature{NONE,LOGX,LOGY,LOGXY};
}

#endif

