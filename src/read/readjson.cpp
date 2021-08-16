
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

void readXdata(const json11::Json& json_obj,std::vector<double>& x)
{
    if(json_obj["x"].is_array()){
        const json11::Json::array& json_x = json_obj["x"].array_items();
        x.resize(json_x.size());
        for(auto i = 0; i < json_x.size(); i++)
            x[i] = json_x[i].number_value();
    } else{
        if(!json_obj["xlabel"].is_string()){
            const std::string str("Failed to readXY data: no 'x' data or 'xlabel' \
                    found in Json object.");
            throw std::domain_error(str);
        }
        const std::string& xlabel = json_obj["xlabel"].string_value();
        if(!json_obj[xlabel].is_array()){
            const std::string str("Failed to readXY data: \
                    no 'x' data or " + xlabel + " data found in Json object.");
            throw std::domain_error(str);
        }
        const json11::Json::array& json_x = json_obj[xlabel].array_items();
        x.resize(json_x.size());
        for(auto i = 0; i < json_x.size(); i++)
            x[i] = json_x[i].number_value();
    }
}

void readYdata(const json11::Json& json_obj,std::vector<double>& y)
{
    if(json_obj["y"].is_array()){
        const json11::Json::array& json_y = json_obj["y"].array_items();
        y.resize(json_y.size());
        for(auto i = 0; i < json_y.size(); i++)
            y[i] = json_y[i].number_value();
    } else{
        if(!json_obj["ylabel"].is_string()){
            const std::string str("Failed to readXY data: no 'y' data or 'ylabel' \
                    found in Json object.");
            throw std::domain_error(str);
        }
        const std::string& ylabel = json_obj["ylabel"].string_value();
        if(!json_obj[ylabel].is_array()){
            const std::string str("Failed to readXY data: \
                    no 'y' data or " + ylabel + " data found in Json object.");
            throw std::domain_error(str);
        }
        const json11::Json::array& json_y = json_obj[ylabel].array_items();
        y.resize(json_y.size());
        for(auto i = 0; i < json_y.size(); i++)
            y[i] = json_y[i].number_value();
    }
}

pw::metadataMap readXY(const std::filesystem::path& path,std::vector<double>& x,\
        std::vector<double>& y)
{
    pw::metadataMap metadata = getMetaData(path);
    json11::Json json_obj;
    readJsonObject(path,json_obj);
    readXdata(json_obj,x);
    readYdata(json_obj,y);
    return metadata;
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











