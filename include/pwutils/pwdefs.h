// pwdefs.h
#pragma once

#include <map>

namespace pw{
    using metadataMap = std::map<std::string,std::string>;
    using metadataPair = std::pair<std::string,std::string>;
    enum class FileSignature{DAT,JSON,UNKNOWN};
    enum class DataSignature{XY,XCVY,XYZ,XYCVZ,UNKNOWN};
    enum class OperatorSignature{NONE,LOGX,LOGY,LOGXLOGY,LOGZ};
}


