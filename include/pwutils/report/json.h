
#ifndef JSON_H_
#define JSON_H_ 

#include "pwutils/report/reportdata.h"
#include "pwutils/report/reporthelper.h"
#include <complex> 
#include <string> 
#include <vector> 
#include <memory>
#include <fstream>
#include <map> 

namespace json{

using pw::dcmplx;         

void writeJSONLabel(std::ofstream& os,const std::string& label,const std::string& indent="\t");
void writeJSONValue(std::ofstream& os,const std::string& value,
		const std::string& indent="",bool end_value=false);
void writeJSONVector(std::ofstream& os,const std::string& label,const std::vector<double>& v,
		const std::string& indent="\t",bool end_value=false,int precision=pw::REPORT_PRECISION);
void writeJSONVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,
		const std::string& indent="\t",bool end_value=false,int precision=pw::REPORT_PRECISION);
void writeJSONPowerVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,
		const std::string& indent="\t",bool end_value=false,int precision=pw::REPORT_PRECISION);
void writeJSONPhaseVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,
		const std::string& indent="\t",bool end_value=false,int precision=pw::REPORT_PRECISION);
void mapToJSON(std::ofstream& os,const pw::metadataMap& str_map,bool end_value=false);


class ReportRealData1D : public pw::VBReportRealData1D
{
    public:
        ReportRealData1D(const std::string& name,
            const std::vector<double>& x, 
            const std::vector<double>& y, 
            const std::string& x_label = "x",
            const std::string& y_label = "y") : 
                pw::VBReportRealData1D(name,x,y,x_label,y_label) {
                    pw::VBReport::setFileExtension("json");}
        ~ReportRealData1D() {};
        void report(std::ofstream& os) const {
            os << "{" << std::endl;
            if(VBReportData::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }
    private:
		void reportMetadata(std::ofstream& os) const {mapToJSON(os,this->metadata(),false);}
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
                    pw::VBReport::setFileExtension("json");}
		~ReportComplexData1D() {}
        void report(std::ofstream& os) const {
            os << "{" << std::endl;
            if(VBReportData::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }
    private:
		void reportMetadata(std::ofstream& os) const {mapToJSON(os,this->metadata(),false);}
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
                    pw::VBReport::setFileExtension("json"); }
        ~ReportRealData2D() {}
        void report(std::ofstream& os) const {
            os << "{" << std::endl;
            if(VBReportData::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }

    private:
		void reportMetadata(std::ofstream& os) const {mapToJSON(os,this->metadata(),false);}
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
                    pw::VBReport::setFileExtension("json");}
		~ReportComplexData2D() {}
        void report(std::ofstream& os) const {
            os << "{" << std::endl;
            if(VBReportData::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }
    private:
		void reportMetadata(std::ofstream& os) const {mapToJSON(os,this->metadata(),false);}
        void reportData(std::ofstream& os) const;

};

class ReportTracker : public pw::VBReportTracker {
    public:
        ReportTracker(const std::string& nm, const std::string& tlabel="x") : 
            pw::VBReportTracker(nm,tlabel), m_t() {
                pw::VBReport::setFileExtension("json");}
        virtual ~ReportTracker() {}
        std::vector<double>& getT() {return m_t;}
		void report(std::filesystem::path& filePath,double t){
            std::ofstream os(filePath.string(),std::ios::trunc);
            os << "{" << std::endl;
		    if(VBReport::metadataOn()){
                reportMetadata(os);
            }
		    reportTracker(os,t);
            os << "}" << std::endl;
        }
    private:
        std::vector<double> m_t;
		void reportMetadata(std::ofstream& os) const {mapToJSON(os,this->metadata(),false);}
		virtual void reportTracker(std::ofstream& os,double t) = 0;
};

class ReportRealTrackerMax : public ReportTracker
{
    public:
        ReportRealTrackerMax(const std::string& nm,const std::vector<double>& v,
                const std::string& tlabel = "x",const std::string& ylabel="y") :
            ReportTracker(nm,tlabel), m_v(v),m_ylabel(ylabel) {}
        ~ReportRealTrackerMax() {}
        std::string getLabelY() const {return m_ylabel;}
    private:
        const std::vector<double>& m_v;
        std::string m_ylabel;
        std::vector<double> m_y;
		void reportTracker(std::ofstream& os,double t);
};

class ReportComplexTrackerMax : public ReportTracker
{
    public:
        ReportComplexTrackerMax(const std::string& nm,const std::vector<dcmplx>& v,
                const std::string& tlabel = "x", const std::string& ylabel="y") :
            ReportTracker(nm,tlabel), m_v(v),m_ylabel(ylabel) {}
        ~ReportComplexTrackerMax() {}
        std::string getLabelY() const {return m_ylabel;}
    private:
        const std::vector<dcmplx>& m_v;
        std::string m_ylabel;
        std::vector<double> m_y;
		void reportTracker(std::ofstream& os,double t);
};






}

#endif


