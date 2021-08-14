
#include "pwutils/read/readjson.h"
#include "pwutils/pwstrings.h"
#include "pwutils/pwmath.hpp"
#include <string>
#include <map>

namespace json{

pw::DataSignature dataSignature(const std::filesystem::path& path) {
    return pw::DataSignature::UNKNOWN;
//    std::fstream stream{path};
//    pw::metadataMap meta_map = getHeaderContent(stream);
//    if(meta_map.find("DataSignature") != meta_map.end())
//        return static_cast<pw::DataSignature>(std::stoi(meta_map["DataSignature"]));
//    else
//        return deduceDataSignature(fin);
}

pw::OperatorSignature operatorSignature(const std::filesystem::path& path)
{
    return pw::OperatorSignature::NONE;
//    std::fstream stream{path};
//    pw::metadataMap meta_map = getHeaderContent(stream);
//    if(meta_map.find("OperatorSignature") != meta_map.end())
//        return static_cast<pw::OperatorSignature>(std::stoi(meta_map["OperatorSignature"]));
//    else
//        return pw::OperatorSignature::NONE;
}

//pw::DataSignature deduceDataSignature(std::ifstream& fin)
//{
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
//    return pw::DataSignature::UNKNOWN;
//}
//





}











