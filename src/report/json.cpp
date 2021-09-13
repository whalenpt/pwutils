
#include "pwutils/report/json.hpp"
#include "pwutils/report/reporthelper.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <map>

namespace json{

// Complex value specialization of writeJSONVector
template<>
void writeJSONVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,\
        unsigned int stride,const std::string& indent,bool end_value)
{
    std::string two_indent = indent + indent;
    writeJSONLabel(os,label,indent);
    os << "{" << std::endl;
    writeJSONLabel(os,"dtype",two_indent);
    writeJSONValue(os,"complex128");

    unsigned int i;
    writeJSONLabel(os,"real",two_indent);
    os << "[";
    for(i=0; i < v.size()-stride; i+=stride)
    	os << v[i].real() << ", ";
    os << v[i].real() << "]," << std::endl;

    writeJSONLabel(os,"imag",two_indent);
    os << "[";
    for(i = 0; i < v.size()-stride; i+=stride)
    	os << v[i].imag() << ", ";
    os << v[i].imag() << "]" << std::endl;

    std::string end_string = end_value ? "}" : "},";
    os << indent << end_string << std::endl;
}


void streamToJSON(std::ofstream& os,const pw::metadataMap& str_map) 
{
    pw::metadataMap::const_iterator it;
    for(it = str_map.begin(); it!= str_map.end(); it++){
        writeJSONLabel(os,(*it).first);
        writeJSONValue(os,(*it).second);
    }
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

void writeJSONPowerVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,\
        unsigned int stride,const std::string& indent,bool end_value)
{
    writeJSONLabel(os,label,indent);
	os << "[";
    unsigned int i;
	for(i=0; i < v.size()-stride; i+=stride){
        os << pow(abs(v[i]),2) << ", ";
	}
    std::string end_string = end_value ? "]" : "],";
	os << pow(abs(v[i]),2) << end_string << std::endl;
}

void writeJSONPhaseVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,\
        unsigned int stride,const std::string& indent,bool end_value)
{
		std::vector<double> phaseVec(v.size(),0.0);
        unsigned int count = 0;
        unsigned int i;
		for(i = 0; i < v.size(); i+=stride){
            phaseVec[count] = arg(v[i]);
            count++;
        }
        phaseVec[count] = arg(v[i]);
        count++;
        phaseVec.resize(count);
		pw::AdjustPhase(phaseVec,count);
		writeJSONVector(os,label,phaseVec,1,indent,end_value);
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


/*

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
*/



}







