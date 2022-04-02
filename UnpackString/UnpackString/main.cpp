#include <filesystem>
#include <fstream>
#include <iostream>

#include "methods.hpp"

int main(const int argc, char** argv)
{
    //Check if file to unpack is provided
    if (argc <= 1)
    {
        std::cerr << "You should provide file that contains string to unpack as program argument" << std::endl;
        return 1;
    }
    //Create a file stream for file to unpack
    std::ifstream file{ argv[1] };

    //Open file
    if (!file.is_open())
    {
        std::cerr << "Unable to open the file!" << std::endl;
        return 1;
    }

    std::string str;
    file >> str; //output file contents

    try
    {
        const std::string unpackedString = UnpackString(str);
        const auto splitted = Split_String_Limit(unpackedString, 40);

        using namespace std::filesystem;
        path outFilePath{ argv[1] };
        //name unpacked file
        outFilePath.replace_filename("unpacked_" + outFilePath.filename().string());
        //output file
        std::ofstream outFile{ outFilePath };
        //File contents
        for (const auto& str : splitted)
        {
            outFile << str << std::endl;
        }
    }
    //Error exception
    catch (std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
}
