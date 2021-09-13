
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

template<>
void writeColVec(std::ofstream& os,const std::vector<dcmplx>& x)
{
	for(unsigned int i = 0; i < x.size(); i++){
		os << x[i].real() << " " <<  x[i].imag() << std::endl;
	}
}

void TrackComplexData::reportData(std::ofstream& os) const 
{
	if(getComplexOp() == pw::ComplexOp::None)
        writeDat1D(os,this->getX(),this->getY());
    else
        writeDat1D(os,this->getX(),this->getOpY());
}



}

