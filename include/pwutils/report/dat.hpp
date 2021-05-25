
#ifndef DAT_HPP_
#define DAT_HPP_ 

#include <complex> 
#include <string> 
#include <vector> 
#include <map> 
#include <fstream>
#include <cassert>
#include "pwutils/report/reportbase.h"
#include "pwutils/report/reporthelper.h"

namespace dat{

using pw::dcmplx;

void streamToDat(std::ofstream& os,const pw::metadataMap& str_map);

template<typename T1,typename T2>
void writeDatRow1D(std::ofstream& os,T1 x,T2 y,int precision=pw::REPORT_PRECISION)
{
    os << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << x \
       << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << y << std::endl;
}

template<typename T1,typename T2>
void writeDat1D(std::ofstream& os,const std::vector<T1>& x,const std::vector<T2>& y,int precision=pw::REPORT_PRECISION) 
{
    assert (x.size() == y.size());
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << x[i] \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << y[i] << std::endl;
	}
}

template<typename T1>
void writeDat1D(std::ofstream& os,const std::vector<T1>& x,\
    const std::vector<dcmplx>& y,int precision=pw::REPORT_PRECISION)
{
    assert (x.size() == y.size());
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << x[i] \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << y[i].real() \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << y[i].imag()
		   << std::endl;
	}
}


template<typename T1>
void writePowerDat1D(std::ofstream& os,const std::vector<T1>& x,\
    const std::vector<dcmplx>& y,int precision=pw::REPORT_PRECISION)
{
    assert (x.size() == y.size());
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << x[i] \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) \
		   << pow(abs(y[i]),2) << std::endl;
	}
}

template<typename T1>
void writePhaseDat1D(std::ofstream& os,const std::vector<T1>& x,
        const std::vector<dcmplx>& y,int precision)
{
    assert (x.size() == y.size());
    std::vector<double> phaseVec(y.size());
    for(unsigned int i=0; i < y.size(); i++)
        phaseVec[i] = arg(y[i]);
    pw::AdjustPhase(phaseVec,phaseVec.size());
    writeDat1D(os,x,phaseVec,precision);
}


/*
void writeDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
    const std::vector<double>& z,int precision=pw::REPORT_PRECISION); 
void writeDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
    const std::vector<dcmplx>& z,int precision=pw::REPORT_PRECISION); 
void writePhaseDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
    const std::vector<dcmplx>& z,int precision=pw::REPORT_PRECISION); 
void writePowerDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
    const std::vector<dcmplx>& z,int precision=pw::REPORT_PRECISION); 
*/

template<typename T1>
void writeRowVec(std::ofstream& os,const std::vector<T1>& x,int precision=pw::REPORT_PRECISION) {
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << x[i]; 
    }
	os << std::endl;
}

template<typename T1>
void writeColVec(std::ofstream& os,const std::vector<T1>& x,int precision=pw::REPORT_PRECISION)
{
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) \
		   << std::setw(precision+pw::REPORT_PADING) << x[i] << std::endl; 
    }
}

template<>
void writeColVec(std::ofstream& os,const std::vector<dcmplx>& x,int precision)
{
	for(unsigned int i = 0; i < x.size(); i++){
		os << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << x[i].real() \
		   << std::scientific << std::setprecision(precision) << std::setw(precision+pw::REPORT_PADING) << x[i].imag() \
		   << std::endl;
	}
}

template<class T1,class T2>
class ReportData1D : public pw::VBReportData1D<T1,T2>
{
    public:
        ReportData1D(const std::string& name,
            const std::vector<T1>& x, 
            const std::vector<T2>& y, 
            const std::string& x_label = "x",
            const std::string& y_label = "y") : 
                pw::VBReportData1D<T1,T2>(name,x,y,x_label,y_label) {
                    pw::VBReport::setFileExtension("dat");}
        ~ReportData1D() {};
    private:
		void reportMetadata(std::ofstream& os) const {streamToDat(os,this->metadata());}
		void reportData(std::ofstream& os) const; 
};

template<class T1,class T2>
void ReportData1D<T1,T2>::reportData(std::ofstream& os) const
{
    writeDat1D(os,this->getX(),this->getY(),this->precision());
}

template<class T1>
class ReportComplexData1D : public pw::VBReportComplexData1D<T1>
{
	public :
        ReportComplexData1D(const std::string& name,
            const std::vector<T1>& x,
            const std::vector<dcmplx>& y,
            std::string x_label="x",
            std::string y_label="y") : 
                pw::VBReportComplexData1D<T1>(name,x,y,x_label,y_label) {
                    pw::VBReport::setFileExtension("dat");}
		~ReportComplexData1D() {}
    private:
		void reportMetadata(std::ofstream& os) const {streamToDat(os,this->metadata());}
		void reportData(std::ofstream& os) const; 
};

template<class T1>
void ReportComplexData1D<T1>::reportData(std::ofstream& os) const
{
    if(this->getPhase())
		writePhaseDat1D(os,this->getX(),this->getY(),this->precision());
    else if(this->getPower()){
		writePowerDat1D(os,this->getX(),this->getY(),this->precision());
	} else
        writeDat1D(os,this->getX(),this->getY(),this->precision());
}


/*
class ReportRealData2D : public pw::VBReportRealData2D
{
    public:
        ReportRealData2D(const std::string& name,
            const std::vector<double>& x,
            const std::vector<double>& y,
            const std::vector<double>& z,
            std::string x_label = "x",
            std::string y_label = "y",
            std::string z_label = "z") : pw::VBReportRealData2D(
                name,x,y,z,x_label,y_label,z_label) {
                    pw::VBReport::setFileExtension("dat"); }
        ~ReportRealData2D() {}
    private:
		void reportMetadata(std::ofstream& os) const {streamToDat(os,this->metadata());}
		void reportData(std::ofstream& os) const; 
};

class ReportComplexData2D : public pw::VBReportComplexData2D
{
    public:
        ReportComplexData2D(const std::string& name,
            const std::vector<double>& x,
            const std::vector<double>& y,
            const std::vector<dcmplx>& z,
            std::string x_label = "x",
            std::string y_label = "y",
            std::string z_label = "z") : pw::VBReportComplexData2D(
                name,x,y,z,x_label,y_label,z_label) {
                    pw::VBReport::setFileExtension("dat");}
		~ReportComplexData2D() {}
    private:
		void reportMetadata(std::ofstream& os) const {streamToDat(os,this->metadata());}
		void reportData(std::ofstream& os) const; 
};

class ReportTracker : public pw::VBReportTracker {
    public:
        ReportTracker(const std::string& nm,const std::string& tlabel="x") : 
            pw::VBReportTracker(nm,tlabel) {
                pw::VBReport::setFileExtension("dat");}

        virtual ~ReportTracker() {}
		void report(std::filesystem::path& filePath,double t){
            std::ofstream os(filePath.string(),std::ios::app);
		    if(VBReport::metadataOn()){
		        reportMetadata(os);
                VBReport::setReportMetadata(false);
            }
		    reportTracker(os,t);
        }
    private:
		void reportMetadata(std::ofstream& os) const {streamToDat(os,this->metadata());}
		virtual void reportTracker(std::ofstream& os,double t) = 0;
};

class ReportRealTrackerMax : public ReportTracker
{
    public:
        ReportRealTrackerMax(const std::string& nm,const std::vector<double>& v,
                const std::string& tlabel = "x", const std::string& ylabel="y") :
            ReportTracker(nm,tlabel), m_v(v),m_ylabel(ylabel) {}
        ~ReportRealTrackerMax() {}
    private:
        const std::vector<double>& m_v;
        std::string m_ylabel;
		void reportTracker(std::ofstream& os,double t) const;
};

class ReportComplexTrackerMax : public ReportTracker
{
    public:
        ReportComplexTrackerMax(const std::string& nm,const std::vector<dcmplx>& v,
                const std::string& tlabel = "x", const std::string& ylabel="y") :
            ReportTracker(nm,tlabel), m_v(v),m_ylabel(ylabel) {}
        ~ReportComplexTrackerMax() {}
    private:
        const std::vector<dcmplx>& m_v;
        std::string m_ylabel;
		void reportTracker(std::ofstream& os,double t) const;
};

*/






}

#endif

