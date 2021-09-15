
#include "pwutils/read/readjson.h"
#include "pwutils/pwstrings.h"
#include "pwutils/pwmath.hpp"
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include <json11/json11.hpp>

namespace json{


pw::metadataMap getMetaData(const std::filesystem::path& path)
{
    std::ifstream stream{path};
    return getMetaData(stream);
}

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
    for(const auto& item : json_map)
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

void readJSONstring(const std::filesystem::path& path,std::string& str)
{
    std::ifstream stream{path};
    stream.clear();
    stream.seekg(0,std::ios::end);
    str.resize(stream.tellg());
    stream.seekg(0,std::ios::beg);
    stream.read(&str[0],str.size());
    stream.close();
}

void readJsonObject(const std::filesystem::path& path,json11::Json& json_obj)
{
    std::string buffer;
    readJSONstring(path,buffer);
    std::string err_str;
    json_obj = json11::Json::parse(buffer,err_str);
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
    const auto json_obj = json11::Json::parse(buffer,err_str);
    const auto& json_map = json_obj.object_items();

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

void readVecData(const json11::Json& json_obj,std::vector<double>& vec,\
        const std::string& id, std::string id_label)
{
    if(json_obj[id].is_array()){
        const json11::Json::array& json_arr = json_obj[id].array_items();
        vec.resize(json_arr.size());
        for(auto i = 0; i < json_arr.size(); i++)
            vec[i] = json_arr[i].number_value();
    } else if(!id_label.empty()){
        if(!json_obj[id_label].is_string()){
            const std::string str("Error in readVecData: id_label " \
                    + id_label + " not found in Json object.");
            throw std::domain_error(str);
        }
        const std::string& label = json_obj[id_label].string_value();
        if(!json_obj[label].is_array()){
            const std::string str("Error in readVecData: id label " + id_label\
                    + " found in json but no " + label + " data supplied.");
            throw std::domain_error(str);
        }
        const json11::Json::array& json_arr = json_obj[label].array_items();
        vec.resize(json_arr.size());
        for(auto i = 0; i < json_arr.size(); i++)
            vec[i] = json_arr[i].number_value();
    } else{
        const std::string str("Error in readVecData: neither id "\
                + id + " nor id_label " + id_label + " were found in the json object"); 
                throw std::domain_error(str);
    }
}

pw::metadataMap readXY(const std::filesystem::path& path,std::vector<double>& x,\
        std::vector<double>& y)
{
    pw::metadataMap metadata = getMetaData(path);
    json11::Json json_obj;
    readJsonObject(path,json_obj);
    readVecData(json_obj,x,"x","xlabel");
    readVecData(json_obj,y,"y","ylabel");
    return metadata;
} 
     
 pw::metadataMap readXCVY(const std::filesystem::path& path,std::vector<double>& x,\
         std::vector<pw::dcmplx>& y)
{
    // Stub implementation
    int N = 20;
    x.assign(N,0.0);
    y.assign(N,0.0);
    return pw::metadataMap({});
} 
     
pw::metadataMap readXCVY(const std::filesystem::path& path,std::vector<double>& x,\
          std::vector<double>& y1,std::vector<double>& y2)
{
    // Stub implementation
    int N = 20;
    x.assign(N,0.0);
    y1.assign(N,0.0);
    y2.assign(N,0.0);
    return pw::metadataMap({});

} 

pw::metadataMap readXYZ(const std::filesystem::path& path,std::vector<double>& x,\
        std::vector<double>& y,std::vector<double>& z)
{
    pw::metadataMap metadata = getMetaData(path);
    json11::Json json_obj;
    readJsonObject(path,json_obj);
    readVecData(json_obj,x,"x","xlabel");
    readVecData(json_obj,y,"y","ylabel");
    readVecData(json_obj,z,"z","zlabel");
    return metadata;
} 
 

pw::metadataMap readXYCVZ(const std::filesystem::path& path,std::vector<double>& x,\
         std::vector<double>& y,std::vector<pw::dcmplx>& z)
{
    // Stub implementation
    int N = 20;
    x.assign(N,0.0);
    y.assign(N,0.0);
    z.assign(N*N,0.0);
    return pw::metadataMap({});
} 
 


}











