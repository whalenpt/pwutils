
#ifndef DAT_H_
#define DAT_H_ 

#include <complex> 
#include <string> 
#include <vector> 
#include <ctime>
#include <map> 
#include <fstream>
#include "pwutils/report/reportdata.h"
#include "pwutils/report/reporthelper.h"

namespace dat{

using pw::dcmplx;

void streamToDat(std::ofstream& os,const pw::metadataMap& str_map);
void writeDatRow1D(std::ofstream& os,double x,double y,int precision=pw::REPORT_PRECISION);
void writeDat1D(std::ofstream& os,const std::vector<double>& x,\
    const std::vector<double>& y,int precision=pw::REPORT_PRECISION);
void writeDat1D(std::ofstream& os,const std::vector<double>& x,\
    const std::vector<dcmplx>& y,int precision=pw::REPORT_PRECISION);
void writePowerDat1D(std::ofstream& os,const std::vector<double>& x,\
    const std::vector<dcmplx>& y,int precision=pw::REPORT_PRECISION);
void writePhaseDat1D(std::ofstream& os,const std::vector<double>& x,
    const std::vector<dcmplx>& y,int precision=pw::REPORT_PRECISION);
void writeDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
    const std::vector<double>& z,int precision=pw::REPORT_PRECISION); 
void writeDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
    const std::vector<dcmplx>& z,int precision=pw::REPORT_PRECISION); 
void writePhaseDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
    const std::vector<dcmplx>& z,int precision=pw::REPORT_PRECISION); 
void writePowerDat2D(std::ofstream& os,const std::vector<double>& x,const std::vector<double>& y,
    const std::vector<dcmplx>& z,int precision=pw::REPORT_PRECISION); 
void writeRowVec(std::ofstream& os,const std::vector<double>& x,int precision=pw::REPORT_PRECISION);
void writeColVec(std::ofstream& os,const std::vector<double>& x,int precision=pw::REPORT_PRECISION);
void writeColVec(std::ofstream& os,const std::vector<dcmplx>& x,int precision=pw::REPORT_PRECISION);


class ReportRealData1D : public pw::VBReportRealData1D
{
    public:
        ReportRealData1D(const std::string& name,
            const std::vector<double>& x, 
            const std::vector<double>& y, 
            const std::string& x_label = "x",
            const std::string& y_label = "y") : 
                pw::VBReportRealData1D(name,x,y,x_label,y_label) {
                    pw::VBReport::setFileExtension("dat");}
        ~ReportRealData1D() {};
    private:
		void reportMetadata(std::ofstream& os) const {streamToDat(os,this->metadata());}
		void reportData(std::ofstream& os) const; 
};

class ReportComplexData1D : public pw::VBReportComplexData1D
{
	public :
        ReportComplexData1D(const std::string& name,
            const std::vector<double>& x,
            const std::vector<dcmplx>& y,
            std::string x_label="x",
            std::string y_label="y") : 
                pw::VBReportComplexData1D(name,x,y,x_label,y_label) {
                    pw::VBReport::setFileExtension("dat");}
		~ReportComplexData1D() {}
    private:
		void reportMetadata(std::ofstream& os) const {streamToDat(os,this->metadata());}
		void reportData(std::ofstream& os) const; 
};

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

class ReportRealVector : public pw::VBReportVector {
    public:
        ReportRealVector(const std::string& nm,std::vector<double>& v,const std::string& label="x") : 
            pw::VBReportVector(nm,label), m_v(v) {
                pw::VBReport::setFileExtension("dat");}
        ~ReportRealVector() {}
    private:
        const std::vector<double>& m_v;
		void reportMetadata(std::ofstream& os) const {streamToDat(os,this->metadata());}
		void reportVector(std::ofstream& os) const {writeColVec(os,m_v,this->precision());}
};

class ReportComplexVector : public pw::VBReportVector {
    public:
        ReportComplexVector(const std::string& nm,std::vector<dcmplx>& v,const std::string& label="x") : 
            pw::VBReportVector(nm,label), m_v(v) {
                pw::VBReport::setFileExtension("dat");}
        ~ReportComplexVector() {}
    private:
        const std::vector<dcmplx>& m_v;
		void reportMetadata(std::ofstream& os) const {streamToDat(os,this->metadata());}
		void reportVector(std::ofstream& os) const {writeColVec(os,m_v,this->precision());}
};






}

#endif


