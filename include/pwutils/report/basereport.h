#ifndef BASEREPORT_H
#define BASEREPORT_H

#include <string>
#include <fstream>
#include <filesystem>
#include <memory>
#include <cassert>
#include "pwutils/pwdefs.h"
#include "pwutils/report/reporthelper.h"

namespace pw{

enum class TrackType { Max,
    Min
};

enum class ComplexOp {None,
    Power
};

class ReportBase{
	public:
		ReportBase(const std::string& nm) 
		  : m_name(nm),m_report_metadata(true),
		  m_metadata_map(),
		  m_extension() {}
		virtual ~ReportBase() {};
		virtual void report(std::ofstream& os) const {
		    if(metadataOn())
		        reportMetadata(os);
		    reportData(os);
        }
		friend std::ofstream& operator<<(std::ofstream& os,const ReportBase& def){ def.report(os);
			return os; }
		friend std::ofstream& operator<<(std::ofstream& os,const ReportBase* def){ def->report(os);
			return os; }
		friend std::ofstream& operator<<(std::ofstream& os,const std::unique_ptr<ReportBase> def){ \
		    def->report(os); return os; }

        void setFileSignature(FileSignature file_sig);
        void setDataSignature(DataSignature data_sig);
        void setOperatorSignature(OperatorSignature op_sig);
        FileSignature fileSignature() const;
        DataSignature dataSignature() const;
        OperatorSignature operatorSignature() const;

		void setItem(const std::string& key,double val);
		void setItem(const std::string&,const std::string&); 
		void removeItem(const std::string&); 
		void setReportMetadata(bool val) {m_report_metadata = val;}
		void setFileExtension(const std::string& extension) {
		    m_extension=extension;}

		std::string getName() const {return m_name;}
		const metadataMap& getMetadata() const {return m_metadata_map;} 
		std::string getFileExtension() const {return m_extension;}

        std::filesystem::path path(const std::filesystem::path& dir_path) const
            { return pw::filePath(dir_path,m_name,m_extension);}
        std::filesystem::path path(const std::filesystem::path& dir_path,int repNum) const
            { return pw::filePath(dir_path,m_name,repNum,m_extension);}
		bool metadataOn() const {return m_report_metadata;}

	private:
		const std::string m_name;
		bool m_report_metadata;
        metadataMap m_metadata_map; 
        std::string m_extension;
		virtual void reportMetadata(std::ofstream& os) const = 0;
		virtual void reportData(std::ofstream& os) const = 0;
};

// Need a non-templated base class for holding all ReportData1D instances in an STL container
// without specifying a data type (which is dictated by the template subclass)
class ReportData1D : public ReportBase
{
	public:
		ReportData1D(const std::string& nm) 
		  : ReportBase(nm) {
                setLabelX("x");
                setLabelY("y");
            }
		virtual ~ReportData1D() {}
		std::string getLabelX() const {return m_xlabel;}
		std::string getLabelY() const {return m_ylabel;}
		void setLabelX(const std::string& xlabel) {m_xlabel=xlabel;
            ReportBase::setItem("xlabel",xlabel);
		}
		void setLabelY(const std::string& ylabel) {m_ylabel=ylabel;
            ReportBase::setItem("ylabel",ylabel);
		}

	private:
		virtual void reportData(std::ofstream& os) const = 0;
		std::string m_xlabel;
		std::string m_ylabel;

};


// Need a non-templated base class for holding all TrackData instances in an STL container
// without specifying a data type (which is dictated by the template subclass)
class TrackData : public ReportBase
{
	public:
		TrackData(const std::string& nm,TrackType ttype) 
		  : ReportBase(nm), m_ttype(ttype) {}
		virtual ~TrackData() {}
		virtual void updateTracker(double t) = 0; // assume time t is a double value (or convert to)
		const TrackType getTrackType() {return m_ttype;}
		void setTrackType(TrackType ttype) {m_ttype = ttype;}
		std::string getLabelX() const {return m_xlabel;}
		std::string getLabelY() const {return m_ylabel;}
		void setLabelX(const std::string& xlabel) {m_xlabel=xlabel;
            ReportBase::setItem("xlabel",xlabel);
		}
		void setLabelY(const std::string& ylabel) {m_ylabel=ylabel;
            ReportBase::setItem("ylabel",ylabel);
		}
    private:
        TrackType m_ttype;
		virtual void reportData(std::ofstream& os) const = 0;
		std::string m_xlabel;
		std::string m_ylabel;

};

// Need a non-templated base class for holding all ReportData1D instances in an STL container
// without specifying a data type (which is dictated by the template subclass)
class ReportData2D : public ReportBase
{
	public:
		ReportData2D(const std::string& nm) :
            ReportBase(nm),
            m_strideX(1), 
            m_strideY(1) {
                setLabelX("x");
                setLabelY("y");
                setLabelZ("z");
            }
		virtual ~ReportData2D() {}
        std::string getLabelX() const {return m_xlabel;}
        std::string getLabelY() const {return m_ylabel;}
        std::string getLabelZ() const {return m_zlabel;}
        void setLabelX(const std::string& label) {
            m_xlabel = label;
            ReportBase::setItem("xlabel",label);
        }
        void setLabelY(const std::string& label) {
            m_ylabel = label;
            ReportBase::setItem("ylabel",label);
        }
        void setLabelZ(const std::string& label) {
            m_zlabel = label;
            ReportBase::setItem("zlabel",label);
        }
		unsigned int getStrideX() const {return m_strideX;}
		unsigned int getStrideY() const {return m_strideY;}
		void setStrideX(unsigned int strideX) { assert (strideX >= 1);
		    m_strideX  = strideX;}
		void setStrideY(unsigned int strideY) { assert (strideY >= 1);
		    m_strideY  = strideY;}
	private:
		virtual void reportData(std::ofstream& os) const = 0;
		unsigned int m_strideX;
		unsigned int m_strideY;
        std::string m_xlabel;
        std::string m_ylabel;
        std::string m_zlabel;
};



}




#endif
