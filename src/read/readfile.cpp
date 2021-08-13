
#include <fstream>
#include <vector>
#include <string>
#include <ios>
#include "pwutils/read/readfile.h"
#include "pwutils/pwstrings.h"
#include "pwutils/pwmath.hpp"

namespace pw{

    void openFile(const std::string& fname,std::ifstream& fin) {
        fin.open(fname.c_str());
        if(!fin.is_open())
            throw std::ios_base::failure("Failed to open file: " + fname);
    }

    DataFileSignature deduceDataFileType(const std::string& fname){
        std::vector<std::string> fname_vec = pw::parseString(fname,'.');
        if(fname_vec.empty()){
            std::ifstream infile;
            openFile(fname,infile);
            return deduceDataFileSignature(infile);
        } 
        if(fname_vec.back() == "json")
            return DataFileSignature::JSON;
        if(fname_vec.back() == "dat")
            return DataFileSignature::DAT;
        return DataFileSignature::UNKNOWN;
    }

    DataFileSignature deduceDataFileSignature(std::ifstream& fin)
    {
        std::string line;
        while(std::getline(fin,line)){
            line = pw::eatWhiteSpace(line);
            if(line.empty())
                continue;
            else if(line == "{"){
                // JSON? check to be sure
                return checkJSONSignature(fin,line);
            } else if(line[0] == '#'){
                std::vector<std::string> line_data;
                getDatLineData(fin,line_data);
                return checkDatSignature(fin,line_data);
            } else
                return DataFileSignature::UNKNOWN;
        }
        return DataFileSignature::UNKNOWN;
    }

    DataFileSignature checkDatSignature(std::ifstream& fin,std::vector<std::string>& line_data){
        if(!pw::rowIsDoubles(line_data))
            return DataFileSignature::UNKNOWN;
        // found a row of double data
        getDatLineData(fin,line_data);
        if(!pw::rowIsDoubles(line_data))
            return DataFileSignature::UNKNOWN;
        return DataFileSignature::DAT;
    }

    void getDatLineData(std::ifstream& infile,std::vector<std::string>& line_data)
    {
        std::string line_feed;
        while(std::getline(infile,line_feed)){
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

    DataFileSignature checkJSONSignature(std::ifstream& fin,std::string& line){
        if(std::getline(fin,line)){
            line  = pw::eatWhiteSpace(line);
            // Check the first line to see if its in JSON form
            if(!checkJSONline(line))
                return DataFileSignature::UNKNOWN;
            if(&line.back() == std::string(",")){
                // Check second line
                if(std::getline(fin,line))
                    if(checkJSONline(line))
                        return DataFileSignature::JSON;
            } else
                return DataFileSignature::JSON;
        }
        return DataFileSignature::UNKNOWN;
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





}






