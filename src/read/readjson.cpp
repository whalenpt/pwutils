
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

    size_t length = 16;
    char* buffer = new char[length+1];
    std::string metastring;
    bool search = true;
    // read until first array is found
    while(search && iss.read(buffer,length)){
        buffer[length] = '\0';
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
            throw std::domain_error("Failed to find any vector data in the JSON file");
    }
    auto index  = metastring.find_last_of(',');
    metastring = metastring.substr(0,index);
    metastring += '\n';
    metastring += '}';

    delete [] buffer;
    
    std::string err_str;
    const auto meta_json = json11::Json::parse(metastring,err_str);
    const auto& json_map = meta_json.object_items();
    pw::metadataMap metamap;
    for(const auto item : json_map)
        metamap.insert(std::pair(item.first,item.second.string_value()));
    return metamap;
}

pw::DataSignature dataSignature(const std::filesystem::path& path) {
    std::ifstream stream{path};
    pw::metadataMap meta_map = getMetaData(stream);
//    for(const auto& item : meta_map)
//        std::cout << item.first << " : " << item.second << std::endl;
    if(meta_map.find("DataSignature") != meta_map.end())
        return static_cast<pw::DataSignature>(std::stoi(meta_map["DataSignature"]));
    else
        return deduceDataSignature(stream);
}

pw::DataSignature deduceDataSignature(std::ifstream& fin)
{
    fin.clear();
    fin.seekg(0,std::ios::end);
    std::string buffer;
    buffer.resize(fin.tellg());
    fin.seekg(0,std::ios::beg);
    fin.read(&buffer[0],buffer.size());
    fin.close();

    std::string err_str;
    const auto meta_json = json11::Json::parse(buffer,err_str);
    const auto& json_map = meta_json.object_items();

    // count number of vectors (data elements)
    int numarrs = 0;
    for(const auto& item : json_map){
        if(item.second.is_array())
            numarrs++;
    }

    if(numarrs == 2)
        return pw::DataSignature::XY;
    else if(numarrs == 3)
        return pw::DataSignature::XYZ;

    return pw::DataSignature::UNKNOWN;



//    static int num = 0;
//    std::filesystem::path path = std::filesystem::current_path();
//    path /= std::filesystem::path("check_buffer_" + std::to_string(num) + ".txt");
//    std::ofstream out{path};
//    out << buffer;
//    out.close();
//    std::cout << path << std::endl;
//    num++;

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











