
#include "pwutils/report/dat.h"
#include "pwutils/report/reporthelper.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <iostream>


namespace dat{

using pw::dcmplx;
using pw::REPORT_PADING;

void ReportComplexData1D::reportData(std::ofstream& os) const
{
    if(this->getPhase())
		writePhaseDat1D(os,this->getX(),this->getY(),this->precision());
    else if(this->getPower()){
		writePowerDat1D(os,this->getX(),this->getY(),this->precision());
	} else
        writeDat1D(os,this->getX(),this->getY(),this->precision());
}

void ReportComplexData2D::reportData(std::ofstream& os) const
{
    if(this->getPhase())
		writePhaseDat2D(os,this->getX(),this->getY(),this->getZ(),\
		        this->precision());
    else if(this->getPower()){
		writePowerDat2D(os,this->getX(),this->getY(),this->getZ(),\
		        this->precision());
	} else
        writeDat2D(os,this->getX(),this->getY(),this->getZ(),this->precision());
}

void ReportRealData1D::reportData(std::ofstream& os) const
{
    writeDat1D(os,this->getX(),this->getY(),this->precision());
}

void ReportRealData2D::reportData(std::ofstream& os) const
{
    writeDat2D(os,this->getX(),this->getY(),this->getZ(),this->precision());
}

void ReportRealTrackerMax::reportTracker(std::ofstream& os,double t) const
{
    writeDatRow1D(os,t,*std::max_element(m_v.begin(),m_v.end()),this->precision());
}

void ReportComplexTrackerMax::reportTracker(std::ofstream& os,double t) const
{
    double max_val = 0;
    for(auto val : m_v)
        max_val = std::max(abs(val),max_val);
    writeDatRow1D(os,t,max_val,this->precision());
}


void streamToDat(std::ofstream& os,const pw::metadataMap& str_map) 
{
    pw::metadataMap::const_iterator it;
    for(it = str_map.begin(); it!= str_map.end(); it++){
        os << "#" << (*it).first + ": " << (*it).second << std::endl;
    }
}

void writeDatRow1D(std::ofstream& os,double x,double y,int precision)
{
    os << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << x \
       << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << y << std::endl;
}

void writeDat1D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,int precision) 
{
    assert (x.size() == y.size());
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << x[i] \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << y[i] << std::endl;
	}
}

void writeDat1D(std::ofstream& os,const std::vector<double>& x,const std::vector<dcmplx>& y,int precision) 
{
    assert (x.size() == y.size());
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << x[i] \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << y[i].real() \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << y[i].imag();
	}
}

void writePowerDat1D(std::ofstream& os,const std::vector<double>& x,
        const std::vector<dcmplx>& y,int precision)
{
    assert (x.size() == y.size());
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << x[i] \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) \
		   << pow(abs(y[i]),2) << std::endl;
	}
}

void writePhaseDat1D(std::ofstream& os,const std::vector<double>& x,
        const std::vector<dcmplx>& y,int precision)
{
    assert (x.size() == y.size());
    std::vector<double> phaseVec(y.size());
    for(unsigned int i=0; i < y.size(); i++)
        phaseVec[i] = arg(y[i]);
    pw::AdjustPhase(phaseVec,phaseVec.size());
    writeDat1D(os,x,phaseVec,precision);
}

void writeRowVec(std::ofstream& os,const std::vector<double>& x,int precision)
{
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << x[i]; 
    }
	os << std::endl;
}

void writeColVec(std::ofstream& os,const std::vector<double>& x,int precision)
{
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) \
		   << std::setw(precision+REPORT_PADING) << x[i] << std::endl; 
    }
}
void writeColVec(std::ofstream& os,const std::vector<dcmplx>& x,int precision)
{
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << x[i].real() \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+REPORT_PADING) << x[i].imag() \
		   << std::endl;
	}
}

void writeDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
        const std::vector<double>& z,int precision) 
{
    assert (x.size()*y.size() == z.size());
    writeRowVec(os,x,precision);
    writeRowVec(os,y,precision);
    int nx = x.size(); 
    int ny = y.size();
	for(unsigned int i = 0; i < nx; i++){
        for(unsigned int j = 0; j < ny; j++){
            os << std::scientific << std::setprecision(precision) \
                << std::setw(precision+REPORT_PADING) << z[nx*i+j]; 
        }
        os << std::endl;
	}
}

void writeDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
        const std::vector<dcmplx>& z,int precision) 
{
    assert (x.size()*y.size() == z.size());
    writeRowVec(os,x,precision);
    writeRowVec(os,y,precision);
    int nx = x.size(); 
    int ny = y.size();
	for(unsigned int i = 0; i < nx; i++){
        for(unsigned int j = 0; j < ny; j++){
            os << std::scientific << std::setprecision(precision) \
               << std::setw(precision+REPORT_PADING) << z[nx*i+j].real();
            os << std::scientific << std::setprecision(precision) \
               << std::setw(precision+REPORT_PADING) << z[nx*i+j].imag();
        }
        os << std::endl;
	}
}

void writePowerDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
        const std::vector<dcmplx>& z,int precision) 
{
    assert (x.size()*y.size() == z.size());
    writeRowVec(os,x,precision);
    writeRowVec(os,y,precision);
    int nx = x.size(); 
    int ny = y.size();
	for(unsigned int i = 0; i < nx; i++){
        for(unsigned int j = 0; j < ny; j++){
            os << std::scientific << std::setprecision(precision) \
               << std::setw(precision+REPORT_PADING) << pow(abs(z[nx*i+j]),2);
        }
        os << std::endl;
	}
}

void writePhaseDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
        const std::vector<dcmplx>& z,int precision) 
{
    assert (x.size()*y.size() == z.size());
    std::vector<double> phaseVec(z.size());
    for(unsigned int i=0; i < z.size(); i++)
        phaseVec[i] = arg(z[i]);
    pw::AdjustPhase(phaseVec,z.size());
    writeDat2D(os,x,y,phaseVec,precision);
}

}

