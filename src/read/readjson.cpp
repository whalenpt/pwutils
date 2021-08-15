
#include "pwutils/read/readjson.h"
#include "pwutils/pwstrings.h"
#include "pwutils/pwmath.hpp"
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include <json11/json11.hpp>

namespace json{

pw::metadataMap getMetaData(std::ifstream& iss){

    int length = 16;
    char* buffer = new char[length];
    std::string metastring;
    bool search = true;
    // read until first array is found
    while(search && iss.read(buffer,length)){
        std::string temp(buffer);
        auto found = temp.find_first_of('[');
        if(found != std::string::npos){
            metastring += temp.substr(0,found);
            search = false;
        }
        else
            metastring += temp;
    }
    // iss reached end
    if(!iss){
        std::string temp(buffer);
        auto found = temp.find_first_of('[');
        if(found != std::string::npos)
            metastring += temp.substr(0,found);
        else
            throw std::domain_error("Failed to find any data in the JSON file");
    }
    auto index  = metastring.find_last_of(',');
    metastring = metastring.substr(0,index);
    metastring += '\n';
    metastring += '}';

    std::cout << "METAFOUND" << std::endl;
    std::cout << "metastring: " << metastring << std::endl;
    delete [] buffer;

    return pw::metadataMap();
}

pw::DataSignature dataSignature(const std::filesystem::path& path) {
    std::ifstream stream{path};
    pw::metadataMap meta_map = getMetaData(stream);
    if(meta_map.find("DataSignature") != meta_map.end())
        return static_cast<pw::DataSignature>(std::stoi(meta_map["DataSignature"]));
    else
        return deduceDataSignature(stream);
}

pw::DataSignature deduceDataSignature(std::ifstream& fin)
{
//    json11::Json 

//    std::vector<std::string> first_line,second_line,third_line;
//    getLineOfData(fin,first_line);
//    getLineOfData(fin,second_line);
//    getLineOfData(fin,third_line);
//    if(first_line.empty() || second_line.empty() || third_line.empty())
//        return pw::DataSignature::UNKNOWN;
//    if(first_line.size() == second_line.size() == third_line.size()){
//        // Check that all the data is doubles (or perhaps floats, but not ints)
//        if(!(pw::rowIsDoubles(first_line) && pw::rowIsDoubles(second_line) && pw::rowIsDoubles(third_line)))
//            return pw::DataSignature::UNKNOWN;
//        // Assume this is two column data throughout
//        if(first_line.size() == 2)
//            return pw::DataSignature::XY;
//        // Assume this is three column data throughout
//        else if(first_line.size() == 3)
//            return pw::DataSignature::XYcomplex;
//    }
    return pw::DataSignature::UNKNOWN;
}




pw::OperatorSignature operatorSignature(const std::filesystem::path& path)
{
    std::ifstream stream{path};
    pw::metadataMap meta_map = getMetaData(stream);
    if(meta_map.find("OperatorSignature") != meta_map.end())
        return static_cast<pw::OperatorSignature>(std::stoi(meta_map["OperatorSignature"]));
    else
        return pw::OperatorSignature::NONE;
}

pw::metadataMap readXY(const std::filesystem::path& path,std::vector<double>& x,\
        std::vector<double>& y)
{
    int N = 20;
    x.assign(N,0.0);
    y.assign(N,0.0);
    return pw::metadataMap({});
} 
     
 pw::metadataMap readXY_C(const std::filesystem::path& path,std::vector<double>& x,\
         std::vector<pw::dcmplx>& y)
{
    int N = 20;
    x.assign(N,0.0);
    y.assign(N,0.0);
    return pw::metadataMap({});
} 
     
  pw::metadataMap readXY_C(const std::filesystem::path& path,std::vector<double>& x,\
          std::vector<double>& y1,std::vector<double>& y2)
{
    int N = 20;
    x.assign(N,0.0);
    y1.assign(N,0.0);
    y2.assign(N,0.0);
    return pw::metadataMap({});

} 




}











