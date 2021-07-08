#ifndef TRACKBASE_HPP
#define TRACKBASE_HPP

#include <string>
#include <fstream>
#include "pwutils/report/basereport.h"
#include "pwutils/pwmath.hpp"

namespace pw{

enum class TrackType { Max,
    Min
};

enum class ComplexOp {None,
    Power
};

class TrackData : public VBReportData
{
	public:
		TrackData(const std::string& nm,TrackType ttype) 
		  : VBReportData(nm), m_ttype(ttype) {}
		virtual ~TrackData() {}
		virtual void updateTracker(double t) = 0; // assume time t is a double value (or convert to)
		const TrackType getTrackType() {return m_ttype;}
		void setTrackType(TrackType ttype) {m_ttype = ttype;}
    private:
        TrackType m_ttype;
};

template<class T>
class VBTrackData : public TrackData
{
	public:
        VBTrackData(const std::string& name,
            TrackType ttype,
            const std::vector<T>& data, 
            const std::string& x_label = "x",
            const std::string& y_label = "y") : 
                TrackData(name,ttype),m_data(data),
                m_xlabel(x_label),m_ylabel(y_label) {} 
        virtual ~VBTrackData() {};
        const std::vector<double>& getX() const {return m_x;}
        const std::vector<T>& getY() const {return m_y;}
        const std::vector<T>& getData() const {return m_data;}
		std::string getLabelX() const {return m_xlabel;}
		std::string getLabelY() const {return m_ylabel;}
		void setLabelX(const std::string& xlabel) {m_xlabel=xlabel;}
		void setLabelY(const std::string& ylabel) {m_ylabel=ylabel;}
		void updateTracker(double x); 
	private:
        const std::vector<T>& m_data;
        std::vector<double> m_x;
        std::vector<T> m_y;
		std::string m_xlabel;
		std::string m_ylabel;
		virtual void reportData(std::ofstream& os) const = 0;
};

template<class T>
void VBTrackData<T>::updateTracker(double x)
{
    m_x.push_back(x);
    if(getTrackType() == TrackType::Max) {
        m_y.push_back(pw::max(m_data));
    } else if(getTrackType() == TrackType::Min){
        m_y.push_back(pw::min(m_data));
    }
}

class VBTrackComplexData : public VBTrackData<dcmplx>
{
	public:
        VBTrackComplexData(const std::string& name,
            TrackType ttype,
            const std::vector<dcmplx>& data, 
            const std::string& x_label = "x",
            const std::string& y_label = "y",
            ComplexOp cmplxop = ComplexOp::None) : 
                VBTrackData<dcmplx>(name,ttype,data,x_label,y_label),
                m_cmplxop(cmplxop) {}
        virtual ~VBTrackComplexData() {};
        const std::vector<double>& getOpY() const {return m_opy;}
		void updateTracker(double x); 
		void setComplexOp(ComplexOp cmplxop) {m_cmplxop=cmplxop;}
		ComplexOp getComplexOp() const {return m_cmplxop;}
	private:
	    ComplexOp m_cmplxop;
        std::vector<double> m_opy;
		virtual void reportData(std::ofstream& os) const = 0;
};


}




#endif
