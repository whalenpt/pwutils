// json.hpp
#pragma once

#include "pwutils/report/basedata.hpp"
#include "pwutils/report/basetrack.hpp"
#include "pwutils/report/reporthelper.h"
#include "pwutils/pwmath.hpp"
#include <complex> 
#include <string> 
#include <vector> 
#include <memory>
#include <fstream>
#include <iostream>
#include <map> 

namespace json{

using pw::dcmplx;         

void streamToJSON(std::ofstream& os,const pw::metadataMap& str_map);
void writeJSONLabel(std::ofstream& os,const std::string& label,const std::string& indent="\t");
void writeJSONValue(std::ofstream& os,const std::string& value,
		const std::string& indent="",bool end_value=false);

template<typename T>
void writeJSONVector(std::ofstream& os,const std::string& label,const std::vector<T>& v,\
        unsigned int stride=1,const std::string& indent="\t",bool end_value=false)
{
    writeJSONLabel(os,label,indent);
    os << "[";
    unsigned int i;
    for(i = 0; i < v.size()-stride; i+=stride){
    	os << v[i] << ", ";
    }
    std::string end_string = end_value ? "]" : "],";
    os << v[i] << end_string << std::endl;
}

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

template<typename T1,typename T2>
void writeJSON2D_xy(std::ofstream& os,\
        const std::string& xlabel,const std::vector<T1>& x,unsigned int strideX,\
        const std::string& ylabel,const std::vector<T2>& y,unsigned int strideY,\
        const std::string& indent="\t")
{
    writeJSONVector(os,xlabel,x,strideX,indent);
    writeJSONVector(os,ylabel,y,strideY,indent);
}

template<typename T1,typename T2,typename T3>
void writeJSON2D(std::ofstream& os,\
        const std::string& xlabel,const std::vector<T1>& x,unsigned int strideX,\
        const std::string& ylabel,const std::vector<T2>& y,unsigned int strideY,\
        const std::string& zlabel,const std::vector<T3>& z,\
        const std::string& indent="\t")
{
    assert (x.size()*y.size() == z.size());
    writeJSON2D_xy(os,xlabel,x,strideX,ylabel,y,strideY,indent);
    writeJSONLabel(os,zlabel,indent);
	os << "[";
    unsigned int i = 0;
	for(i = 0; i < x.size()-strideX; i+=strideX){
	    for(unsigned int j=0; j < y.size(); j+=strideY){
            os << z[i*y.size()+j] << ", ";
        }
	}
    unsigned int j;
	for(j = 0; j < y.size()-strideY; j++)
        os << z[i*y.size()+j] << ", ";
    os << z[i*y.size()+j];
    os << "]" << std::endl;
}

template<typename T1,typename T2>
void writeJSON2D(std::ofstream& os,\
        const std::string& xlabel,const std::vector<T1>& x,unsigned int strideX,\
        const std::string& ylabel,const std::vector<T2>& y,unsigned int strideY,\
        const std::string& zlabel,const std::vector<dcmplx>& z,\
        const std::string& indent="\t")
{
    assert (x.size()*y.size() == z.size());
    writeJSON2D_xy(os,xlabel,x,strideX,ylabel,y,strideY,indent);
    std::string two_indent = indent + indent;
    writeJSONLabel(os,zlabel,indent);
    os << "{" << std::endl;
    writeJSONLabel(os,"dtype",two_indent);
    writeJSONValue(os,"complex128");

    writeJSONLabel(os,"real",two_indent);
    os << "[";
    unsigned int i;
	for(i=0; i < x.size()-strideX; i+=strideX){
	    for(unsigned int j=0; j < y.size(); j+=strideY){
            os << z[i*y.size()+j].real() << ", ";
        }
	}
    unsigned int j;
	for(j=0; j < y.size()-strideY; j++)
        os << z[i*y.size()+j].real() << ", ";
    os << z[i*y.size()+j].real() << "]," << std::endl;


    writeJSONLabel(os,"imag",two_indent);
    os << "[";
	for(i = 0; i < x.size()-strideX; i+=strideX){
	    for(unsigned int j=0; j < y.size(); j+=strideY){
            os << z[i*y.size()+j].imag() << ", ";
        }
	}
	for(j = 0; j < y.size()-strideY; j++)
        os << z[i*y.size()+j].imag() << ", ";
    os << z[i*y.size()+j].imag() << "]" << std::endl;
    os << indent << "}" << std::endl;
}

template<typename T1,typename T2>
void writeJSONPower2D(std::ofstream& os,\
        const std::string& xlabel,const std::vector<T1>& x,unsigned int strideX,\
        const std::string& ylabel,const std::vector<T2>& y,unsigned int strideY,\
        const std::string& zlabel,const std::vector<dcmplx>& z,\
        const std::string& indent="\t")
{
    assert (x.size()*y.size() == z.size());
    writeJSON2D_xy(os,xlabel,x,strideX,ylabel,y,strideY,indent);
    writeJSONLabel(os,zlabel,indent);
	os << "[";
    unsigned int i = 0;
	for(i = 0; i < x.size()-strideX; i+=strideX){
	    for(unsigned int j=0; j < y.size(); j+=strideY){
            os << pow(abs(z[i*y.size()+j]),2) << ", ";
        }
	}
    unsigned int j;
	for(j = 0; j < y.size()-strideY; j++)
        os << pow(abs(z[i*y.size()+j]),2) << ", ";
    os << pow(abs(z[i*y.size()+j]),2);
    os << "]" << std::endl;
}

template<typename T1,typename T2>
void writeJSONPhase2D(std::ofstream& os,\
        const std::string& xlabel,const std::vector<T1>& x,unsigned int strideX,\
        const std::string& ylabel,const std::vector<T2>& y,unsigned int strideY,\
        const std::string& zlabel,const std::vector<dcmplx>& z,\
        const std::string& indent="\t")
{
    assert (x.size()*y.size() == z.size());
    writeJSON2D_xy(os,xlabel,x,strideX,ylabel,y,strideY,indent);
    writeJSONLabel(os,zlabel,indent);
	os << "[";
    unsigned int i = 0;
	for(i = 0; i < x.size()-strideX; i+=strideX){
	    for(unsigned int j=0; j < y.size(); j+=strideY){
            os << arg(z[i*y.size()+j]) << ", ";
        }
	}
    unsigned int j;
	for(j = 0; j < y.size()-strideY; j++)
        os << arg(z[i*y.size()+j]) << ", ";
    os << arg(z[i*y.size()+j],2);
    os << "]" << std::endl;
}

void writeJSONPowerVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,\
        unsigned int stride=1,const std::string& indent="\t",bool end_value = false);
void writeJSONPhaseVector(std::ofstream& os,const std::string& label,const std::vector<dcmplx>& v,\
        unsigned int stride=1,const std::string& indent="\t",bool end_value=false);
void mapToJSON(std::ofstream& os,const pw::metadataMap& str_map,bool end_value=false);


template<class T1,class T2>
class ReportData1D : public pw::ReportDataBase1D<T1,T2>
{
    public:
        ReportData1D(const std::string& name,
            const std::vector<T1>& x, 
            const std::vector<T2>& y) :
                pw::ReportDataBase1D<T1,T2>(name,x,y) {
                    pw::ReportBase::setFileExtension("json");
                    pw::ReportBase::setFileSignature(pw::FileSignature::JSON);
                }
        ~ReportData1D() {};
    private:
		void reportMetadata(std::ofstream& os) const {streamToJSON(os,this->getMetadata());}
		void reportData(std::ofstream& os) const; 
        void reportImplement(std::ofstream& os) const {
            os << "{" << std::endl;
            if(pw::ReportBase::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }

};

template<class T1,class T2>
void ReportData1D<T1,T2>::reportData(std::ofstream& os) const 
{
	writeJSONVector(os,this->getLabelX(),this->getX(),1,"\t",false);
    writeJSONVector(os,this->getLabelY(),this->getY(),1,"\t",true);
}

template<class T1>
class ReportComplexData1D : public pw::ReportComplexDataBase1D<T1>
{
	public :
        ReportComplexData1D(const std::string& name,
            const std::vector<T1>& x,
            const std::vector<dcmplx>& y) :
                pw::ReportComplexDataBase1D<T1>(name,x,y) {
                    pw::ReportBase::setFileExtension("json");
                    pw::ReportBase::setFileSignature(pw::FileSignature::JSON);
                }
		~ReportComplexData1D() {}
    private:
		void reportMetadata(std::ofstream& os) const {streamToJSON(os,this->getMetadata());}
		void reportData(std::ofstream& os) const; 
        void reportImplement(std::ofstream& os) const {
            os << "{" << std::endl;
            if(pw::ReportBase::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }
};

template<class T1>
void ReportComplexData1D<T1>::reportData(std::ofstream& os) const
{
    writeJSONVector(os,this->getLabelX(),this->getX(),1,"\t",false);
	if(this->getPhase())
		writeJSONPhaseVector(os,this->getLabelY(),this->getY(),1,"\t",true);
    else if(this->getPower()){
	    writeJSONPowerVector(os,this->getLabelY(),this->getY(),1,"\t",true);
	} else
	   writeJSONVector(os,this->getLabelY(),this->getY(),1,"\t",true);
}

template<class T>
class TrackData : public pw::TrackDataBase<T>
{
    public:
        TrackData(const std::string& name,
            pw::TrackType ttype,
            const std::vector<T>& data) :
                pw::TrackDataBase<T>(name,ttype,data) {
                    pw::ReportBase::setFileExtension("json");
                    pw::ReportBase::setFileSignature(pw::FileSignature::JSON);
                }
        ~TrackData() {};
    private:
		void reportMetadata(std::ofstream& os) const {streamToJSON(os,this->getMetadata());}
		void reportData(std::ofstream& os) const; 
        void reportImplement(std::ofstream& os) const {
            os << "{" << std::endl;
            if(pw::ReportBase::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }

};

template<class T>
void TrackData<T>::reportData(std::ofstream& os) const 
{
	writeJSONVector(os,this->getLabelX(),this->getX(),"\t",false);
    writeJSONVector(os,this->getLabelY(),this->getY(),"\t",true);
}

class TrackComplexData : public pw::TrackComplexDataBase
{
    public:
        TrackComplexData(const std::string& name,
            pw::TrackType ttype,
            const std::vector<dcmplx>& data, 
            pw::ComplexOp cmplxop = pw::ComplexOp::None) : 
                pw::TrackComplexDataBase(name,ttype,data,cmplxop) {
                    pw::ReportBase::setFileExtension("json");
                    pw::ReportBase::setFileSignature(pw::FileSignature::JSON);
                }
    private:
		void reportMetadata(std::ofstream& os) const {streamToJSON(os,this->getMetadata());}
		void reportData(std::ofstream& os) const; 
        void reportImplement(std::ofstream& os) const {
            os << "{" << std::endl;
            if(pw::ReportBase::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }

};

void TrackComplexData::reportData(std::ofstream& os) const 
{
	writeJSONVector(os,this->getLabelX(),this->getX(),1,"\t",false);
	if(getComplexOp() == pw::ComplexOp::None)
        writeJSONVector(os,this->getLabelY(),this->getY(),1,"\t",true);
    else
        writeJSONVector(os,this->getLabelY(),this->getOpY(),1,"\t",true);
}


template<class T1,class T2,class T3>
class ReportData2D : public pw::ReportDataBase2D<T1,T2,T3>
{
    public:
        ReportData2D(const std::string& name,
            const std::vector<T1>& x, 
            const std::vector<T2>& y, 
            const std::vector<T3>& z) :
                pw::ReportDataBase2D<T1,T2,T3>(name,x,y,z) {
                    pw::ReportBase::setFileExtension("json");
                    pw::ReportBase::setFileSignature(pw::FileSignature::JSON);
                }
        ~ReportData2D() {};
    private:
		void reportMetadata(std::ofstream& os) const {streamToJSON(os,this->getMetadata());}
		void reportData(std::ofstream& os) const; 
        void reportImplement(std::ofstream& os) const {
            os << "{" << std::endl;
            if(pw::ReportBase::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }

};

template<class T1,class T2,class T3>
void ReportData2D<T1,T2,T3>::reportData(std::ofstream& os) const 
{
    writeJSON2D(os,this->getLabelX(),this->getX(),this->getStrideX(),\
            this->getLabelY(),this->getY(),this->getStrideY(),\
            this->getLabelZ(),this->getZ(),"\t");
}

template<class T1,class T2>
class ReportComplexData2D : public pw::ReportComplexDataBase2D<T1,T2>
{
	public :
        ReportComplexData2D(const std::string& name,
            const std::vector<T1>& x,
            const std::vector<T2>& y,
            const std::vector<dcmplx>& z) :
                pw::ReportComplexDataBase2D<T1,T2>(name,x,y,z) {
                    pw::ReportBase::setFileExtension("json");
                    pw::ReportBase::setFileSignature(pw::FileSignature::JSON);
                }
		~ReportComplexData2D() {}
    private:
		void reportMetadata(std::ofstream& os) const {streamToJSON(os,this->getMetadata());}
		void reportData(std::ofstream& os) const; 
        void reportImplement(std::ofstream& os) const {
            os << "{" << std::endl;
            if(pw::ReportBase::metadataOn())
                reportMetadata(os);
            reportData(os);
            os << "}" << std::endl;
        }
};

template<class T1,class T2>
void ReportComplexData2D<T1,T2>::reportData(std::ofstream& os) const
{
    if(this->getPhase()){
        writeJSONPower2D(os,this->getLabelX(),this->getX(),this->getStrideX(),\
            this->getLabelY(),this->getY(),this->getStrideY(),\
            this->getLabelZ(),this->getZ(),"\t");
    }
    else if(this->getPower()){
        writeJSONPower2D(os,this->getLabelX(),this->getX(),this->getStrideX(),\
            this->getLabelY(),this->getY(),this->getStrideY(),\
            this->getLabelZ(),this->getZ(),"\t");
	} else{
        writeJSON2D(os,this->getLabelX(),this->getX(),this->getStrideX(),\
            this->getLabelY(),this->getY(),this->getStrideY(),\
            this->getLabelZ(),this->getZ(),"\t");
    }
}




}



