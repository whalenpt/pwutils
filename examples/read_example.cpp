
#include <vector>
#include <fstream>
#include <iostream>
#include <pwutils/read/readdat.h>
#include <pwutils/read/readjson.h>
#include <pwutils/read/readfile.h>
#include <pwutils/pwdefs.h>
#include <filesystem>

void print_file_sig(std::filesystem::path& path)
{
    pw::FileSignature file_sig = pw::fileSignature(path);
    if(file_sig == pw::FileSignature::DAT)
        std::cout << path.string() << " : " << "is a DAT format file" << std::endl;
    else if(file_sig == pw::FileSignature::JSON)
        std::cout << path.string() << " : " << "is a JSON format file" << std::endl;
    else if(file_sig == pw::FileSignature::UNKNOWN)
        std::cout << path.string() << " : " << "format is unknown" << std::endl;
    else
        std::cout << path.string() << " : " << "no format specified" << std::endl;
}

int main()
{
    std::filesystem::path input1(std::filesystem::current_path()/std::filesystem::path("data/T_0.json"));
    std::filesystem::path input2(std::filesystem::current_path()/std::filesystem::path("data/T_0.txt"));
    std::filesystem::path input3(std::filesystem::current_path()/std::filesystem::path("data/T_0_sig.txt"));
    std::filesystem::path input4(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0.dat"));
    std::filesystem::path input5(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0.txt"));
    std::filesystem::path input6(std::filesystem::current_path()/std::filesystem::path("data/SQ_T_0_sig.txt"));
    print_file_sig(input1);
    print_file_sig(input2);
    print_file_sig(input3);
    print_file_sig(input4);
    print_file_sig(input5);
    print_file_sig(input6);

    return 0;
}







