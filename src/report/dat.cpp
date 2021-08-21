
#include "pwutils/report/dat.hpp"
#include "pwutils/report/reporthelper.h"
#include <map>
#include <fstream>

namespace dat{

using pw::dcmplx;
using pw::REPORT_PADING;

void streamToDat(std::ofstream& os,const pw::metadataMap& str_map) 
{
    pw::metadataMap::const_iterator it;
    for(it = str_map.begin(); it!= str_map.end(); it++){
        os << "#" << (*it).first + ": " << (*it).second << std::endl;
    }
}



}

