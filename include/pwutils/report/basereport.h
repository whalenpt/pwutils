#ifndef BASEREPORT_H
#define BASEREPORT_H

#include <string>
#include <fstream>
#include <filesystem>
#include <memory>
#include "pwutils/report/reporthelper.h"

namespace pw{

class VBReport{
	public:
		VBReport(const std::string& nm) 
		  : m_name(nm),m_report_metadata(true),
		  m_metadata_map(),
		  m_extension(),
		  m_precision(REPORT_PRECISION) {}
		virtual ~VBReport() {};
		void addItem(const std::string&,const std::string&); 
		void addItem(const std::string&,double); 
		void setItem(const std::string& key,double val);
		void removeItem(const std::string&); 
		void setReportMetadata(bool val) {m_report_metadata = val;}
		void setFileExtension(const std::string& extension) {
		    m_extension=extension;}
		void setPrecision(int precision) {m_precision = precision;}
		int precision() const {return m_precision;}
		std::string name() const {return m_name;}
		bool metadataOn() const {return m_report_metadata;}
		const metadataMap& metadata() const {return m_metadata_map;} 
		std::string fileExtension() const {return m_extension;}
        std::filesystem::path filePath(const std::filesystem::path& dir_path) const
            { return pw::filePath(dir_path,m_name,m_extension);}
        std::filesystem::path filePath(const std::filesystem::path& dir_path,int repNum) const
            { return pw::filePath(dir_path,m_name,repNum,m_extension);}
	private:
		const std::string m_name;
		bool m_report_metadata;
        metadataMap m_metadata_map; 
        std::string m_extension;
		int m_precision;
		virtual void reportMetadata(std::ofstream& os) const = 0;
};

class VBReportData : public VBReport
{
	public:
		VBReportData(const std::string& nm) 
		  : VBReport(nm) {}
		virtual ~VBReportData() {}
		virtual void report(std::ofstream& os) const {
		    if(metadataOn())
		        reportMetadata(os);
		    reportData(os);
        }
		friend std::ofstream& operator<<(std::ofstream& os,const VBReportData& def){ def.report(os);
			return os; }
		friend std::ofstream& operator<<(std::ofstream& os,const VBReportData* def){ def->report(os);
			return os; }
		friend std::ofstream& operator<<(std::ofstream& os,const std::unique_ptr<VBReportData> def){ def->report(os); 
		    return os; }
	private:
		virtual void reportMetadata(std::ofstream& os) const = 0;
		virtual void reportData(std::ofstream& os) const = 0;
};




/*
class VBReportData2D : public VBReportData
{
	public:
        VBReportData2D(const std::string& name) : VBReportData(name) {}
        virtual ~VBReportData2D() {};
		std::string getLabelX() const {return m_xlabel;}
		std::string getLabelY() const {return m_ylabel;}
		std::string getLabelZ() const {return m_zlabel;}
		void setLabelX(const std::string& xlabel) {m_xlabel=xlabel;}
		void setLabelY(const std::string& ylabel) {m_ylabel=ylabel;}
		void setLabelZ(const std::string& zlabel) {m_zlabel=zlabel;}
	private:
		std::string m_xlabel;
		std::string m_ylabel;
		std::string m_zlabel;
		virtual void reportData(std::ofstream& os) const = 0;
};


class VBReportRealData2D : public VBReportData2D
{
    public:
        VBReportRealData2D(const std::string& name,
            const std::vector<double>& x,
            const std::vector<double>& y,
            const std::vector<double>& z,
            std::string x_label = "x",
            std::string y_label = "y",
            std::string z_label = "z") : VBReportData2D(name), m_x(x), m_y(y),
                m_z(z) {setLabelX(x_label); setLabelY(y_label); setLabelZ(z_label);}
        virtual ~VBReportRealData2D() {}
		const std::vector<double>& getX() const {return m_x;}
		const std::vector<double>& getY() const {return m_y;}
		const std::vector<double>& getZ() const {return m_z;}
	private:
        const std::vector<double>& m_x;
        const std::vector<double>& m_y;
        const std::vector<double>& m_z;
		virtual void reportData(std::ofstream& os) const = 0;
};

class VBReportComplexData2D : public VBReportData2D
{
    public:
        VBReportComplexData2D(const std::string& name,
            const std::vector<double>& x,
            const std::vector<double>& y,
            const std::vector<dcmplx>& z,
            std::string x_label = "x",
            std::string y_label = "y",
            std::string z_label = "z") : VBReportData2D(name), m_x(x), m_y(y),
                m_z(z),m_power(false),m_phase(false) {
                    setLabelX(x_label); setLabelY(y_label); setLabelZ(z_label);}
        virtual ~VBReportComplexData2D() {}
		void setPower(bool val) {m_power= val;}  
		void setPhase(bool val) {m_phase = val;}  
		bool getPower() const {return m_power;}
		bool getPhase() const {return m_phase;}
		const std::vector<double>& getX() const {return m_x;}
		const std::vector<double>& getY() const {return m_y;}
		const std::vector<dcmplx>& getZ() const {return m_z;}
	private:
        const std::vector<double>& m_x;
        const std::vector<double>& m_y;
        const std::vector<dcmplx>& m_z;
  		bool m_power;
  		bool m_phase;
		virtual void reportData(std::ofstream& os) const = 0;
};

class VBReportTracker : public VBReport
{
	public:
		VBReportTracker(const std::string& nm,std::string tlabel="x") : 
		    VBReport(nm), m_tlabel(tlabel) {}
		virtual ~VBReportTracker() {}
		std::string getLabelT() const {return m_tlabel;}
		void setLabelT(const std::string& tlabel) {m_tlabel = tlabel;}
		virtual void report(std::filesystem::path& filePath,double t) = 0; 
	private:
		virtual void reportMetadata(std::ofstream& os) const = 0;
		virtual void reportTracker(std::ofstream& os,double t) = 0;
        std::string m_tlabel;
};

*/



}




#endif
