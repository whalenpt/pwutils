
#include "pwutils/report/json.h"
#include "pwutils/report/reporthelper.h"
#include "pwutils/report/reportdata.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <map>

namespace json{

void ReportComplexData1D::reportData(std::ofstream& os) const
{
    writeJSONVector(os,this->getLabelX(),this->getX(),"\t",false,this->precision());
	if(this->getPhase())
		writeJSONPhaseVector(os,this->getLabelY(),this->getY(),"\t",true,this->precision());
    else if(this->getPower()){
	    writeJSONPowerVector(os,this->getLabelY(),this->getY(),"\t",true,this->precision());
	} else
	   writeJSONVector(os,this->getLabelY(),this->getY(),"\t",true,this->precision());
}

void ReportComplexData2D::reportData(std::ofstream& os) const 
{
	writeJSONVector(os,this->getLabelX(),this->getX(),"\t",false,this->precision());
	writeJSONVector(os,this->getLabelY(),this->getY(),"\t",false,this->precision());
    if(this->getPhase())
		writeJSONPhaseVector(os,this->getLabelZ(),this->getZ(),"\t",true,this->precision());
    else if(this->getPower()){
		writeJSONPowerVector(os,this->getLabelZ(),this->getZ(),"\t",true,this->precision());
	} else
	   writeJSONVector(os,this->getLabelZ(),this->getZ(),"\t",true,this->precision());
}

void ReportRealData1D::reportData(std::ofstream& os) const 
{
	writeJSONVector(os,this->getLabelX(),this->getX(),"\t",false,this->precision());
    writeJSONVector(os,this->getLabelY(),this->getY(),"\t",true,this->precision());
}

void ReportRealData2D::reportData(std::ofstream& os) const
{
	writeJSONVector(os,this->getLabelX(),this->getX(),"\t",false,this->precision());
	writeJSONVector(os,this->getLabelY(),this->getY(),"\t",false,this->precision());
	writeJSONVector(os,this->getLabelZ(),this->getZ(),"\t",true,this->precision());
}

void ReportRealTrackerMax::reportTracker(std::ofstream& os,double t) {
    this->getT().push_back(t);
    m_y.push_back(*std::max_element(m_v.begin(),m_v.end()));
    writeJSONVector(os,this->getLabelT(),this->getT(),"\t",false,this->precision());
    writeJSONVector(os,this->getLabelY(),m_y,"\t",true,this->precision());
}

void ReportComplexTrackerMax::reportTracker(std::ofstream& os,double t) {
    this->getT().push_back(t);
    double max_val = 0;
    for(auto val : m_v)
        max_val = std::max(abs(val),max_val);
    m_y.push_back(max_val);
    writeJSONVector(os,this->getLabelT(),this->getT(),"\t",false,this->precision());
    writeJSONVector(os,this->getLabelY(),m_y,"\t",true,this->precision());
}

void writeJSONLabel(std::ofstream& os,const std::string& label, const std::string& indent)
{
	os << indent << "\"" << label <<  "\" : ";
}

void writeJSONValue(std::ofstream& os,const std::string& value,
		const std::string& indent,bool end_value)
{
	std::string end_string = end_value ?  "\"" : "\","; 
    os << indent << "\"" << value << end_string << std::endl;
}

void writeJSONVector(std::ofstream& os,const std::string& label,const std::vector<double>& v,
		const std::string& indent,bool end_value,int precision)
{
	writeJSONLabel(os,label,indent);
	os << "[";
	for(unsigned int i = 0; i < v.size()-1; i++){
		os << std::scientific << std::setprecision(precision) << v[i] << ", ";
	}
	std::string end_string = end_value ?  "]" : "],"; 
	os << v.back() << end_string << std::endl;
}

void writeJSONVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,
		const std::string& indent,bool end_value,int precision)
{
	std::string two_indent = indent + indent;
    writeJSONLabel(os,label,indent);
	os << "{" << std::endl;
    writeJSONLabel(os,"dtype",two_indent);
    writeJSONValue(os,"complex128");
	writeJSONLabel(os,"real",two_indent);
	os << "[";
	for(unsigned int i = 0; i < v.size()-1; i++){
		os << std::scientific << std::setprecision(precision) << v[i].real() << ", ";
	}
	os << v.back().real() << "]," << std::endl;
	writeJSONLabel(os,"imag",two_indent);
	os << "[";
	for(unsigned int i = 0; i < v.size()-1; i++){
		os << std::scientific << std::setprecision(precision) << v[i].imag() << ", ";
	}
	os << v.back().imag() << "]" << std::endl;
	std::string end_string = end_value ?  "}" : "},"; 
	os << indent << end_string << std::endl;
}

void writeJSONPowerVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,
		const std::string& indent,bool end_value,int precision)
{
    writeJSONLabel(os,label,indent);
	os << "[";
	for(unsigned int i = 0; i < v.size()-1; i++){
        os << std::scientific << std::setprecision(precision) << pow(abs(v[i]),2) << ", ";
	}
	std::string end_string = end_value ?  "]" : "],"; 
	os << pow(abs(v.back()),2) << end_string << std::endl;
}

void writeJSONPhaseVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,
		const std::string& indent,bool end_value,int precision)
{
		std::vector<double> phaseVec(v.size());
		for(unsigned int i=0; i < v.size(); i++)
            phaseVec[i] = arg(v[i]);
		pw::AdjustPhase(phaseVec,v.size());
		writeJSONVector(os,label,phaseVec,indent,end_value,precision);
}

void mapToJSON(std::ofstream& os,const pw::metadataMap& str_map,bool end_value) 
{
	pw::metadataMap::const_iterator it;
	for(it = str_map.begin(); it!= str_map.end(); it++){
		writeJSONLabel(os,(*it).first);
		if(std::next(it) == str_map.end())
			writeJSONValue(os,(*it).second,"",end_value);
		else
			writeJSONValue(os,(*it).second,"",false);
	}
}



}







