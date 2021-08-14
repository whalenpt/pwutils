
#include <fstream>
#include <vector>
#include <string>
#include <ios>
#include <filesystem>
#include "pwutils/read/readfile.h"
#include "pwutils/read/readdat.h"
#include "pwutils/read/readjson.h"
#include "pwutils/pwstrings.h"
#include "pwutils/pwmath.hpp"

namespace pw{

    void openFile(const std::string& fname,std::ifstream& fin) {
        fin.open(fname.c_str());
        if(!fin.is_open())
            throw std::ios_base::failure("Failed to open file: " + fname);
    }

    FileSignature fileSignature(const std::filesystem::path& path){
        std::string file_signature = pw::stringLowerCase(path.extension().string());
        if(file_signature == ".json")
            return FileSignature::JSON;
        else if(file_signature == ".dat")
            return FileSignature::DAT;
        return deduceFileSignature(path);
    }

    FileSignature deduceFileSignature(const std::filesystem::path& path)
    {
        std::ifstream stream{path};
        std::string line;
        while(std::getline(stream,line)){
            line = pw::eatWhiteSpace(line);
            if(line.empty())
                continue;
            else if(line == "{"){
                // JSON? check to be sure
                return checkJSONSignature(stream,line);
            } else if(line[0] == '#'){
                std::vector<std::string> line_data;
                getDatLineData(stream,line_data);
                return checkDatSignature(stream,line_data);
            } else
                return FileSignature::UNKNOWN;
        }
        return FileSignature::UNKNOWN;
    }

    FileSignature checkDatSignature(std::ifstream& stream,std::vector<std::string>& line_data){
        if(!pw::rowIsDoubles(line_data))
            return FileSignature::UNKNOWN;
        // found a row of double data
        getDatLineData(stream,line_data);
        if(!pw::rowIsDoubles(line_data))
            return FileSignature::UNKNOWN;
        return FileSignature::DAT;
    }

    void getDatLineData(std::ifstream& stream,std::vector<std::string>& line_data)
    {
        std::string line_feed;
        while(std::getline(stream,line_feed)){
           line_feed = pw::eatWhiteSpace(line_feed);
           // Ignore empty lines and comment lines
           if(line_feed.empty())
               continue;
           else if(line_feed[0] == '#')
               continue;
           else{
               // BINGO
               line_data = pw::parseString(line_feed,' ');
               return;
           }
        }
    }

    FileSignature checkJSONSignature(std::ifstream& stream,std::string& line){
        if(std::getline(stream,line)){
            line  = pw::eatWhiteSpace(line);
            // Check the first line to see if its in JSON form
            if(!checkJSONline(line))
                return FileSignature::UNKNOWN;
            if(&line.back() == std::string(",")){
                // Check second line
                if(std::getline(stream,line))
                    if(checkJSONline(line))
                        return FileSignature::JSON;
            } else
                return FileSignature::JSON;
        }
        return FileSignature::UNKNOWN;
    }

    bool checkJSONline(std::string& line){
        line  = pw::eatWhiteSpace(line);
        std::vector<std::string> colon_data = pw::parseString(line,':');
        if(colon_data.size() != 2)
            // Expect one colon per JSON item
            return false;
        if(colon_data[0].at(0) != '"')
            // Expect Parentheses to start JSON label
            return false;
        return true;
    }

    DataSignature dataSignature(const std::filesystem::path& path,FileSignature file_signature)
    {
        if(file_signature == FileSignature::DAT)
            return dat::dataSignature(path);
        else if(file_signature == FileSignature::JSON)
            return json::dataSignature(path);
        else
            return OperatorSignature::NONE;
    }


    OperatorSignature operatorSignature(const std::filesystem::path& path,FileSignature file_signature)
    {
        if(file_signature == FileSignature::DAT)
            return dat::operatorSignature(path);
        else if(file_signature == FileSignature::JSON)
            return json::operatorSignature(path);
        else
            return OperatorSignature::NONE;
    }



}






