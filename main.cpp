// Created by David Bizon on 19/01/2025.

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include "Config.h"
#include "PchlistToReabankConverter.h"

inline std::string getProgramName(const char* path)
{
    std::string programName(path);
    auto pos = programName.find_last_of("/\\");
    if (pos != std::string::npos)
    {
        programName = programName.substr(pos + 1);
    }
    return programName;
}

inline Config parseArgs(int argc, char** argv)
{
    std::string programName = getProgramName(argv[0]);
    Config config;
    std::vector<const char*> args(argv, argv + argc);
    if (args.size() == 3)
    {
        config.sourceDirectory = args[1];
        config.destinationFile = args[2];
        std::cout << "Source directory: " << config.sourceDirectory << std::endl;
        std::cout << "Destination file: " << config.destinationFile << std::endl;
    }
    else
    {
        throw std::runtime_error("Usage:\n\t" + programName + " <source directory> <destination file>");
    }
    return config;
}

std::vector<std::filesystem::path> findPchlistFiles(const std::filesystem::path& directory)
{
    std::vector<std::filesystem::path> pchlistFiles;
    std::filesystem::directory_iterator filesystemIterator(directory);
    for (const std::filesystem::directory_entry& entry : filesystemIterator)
    {
        if (entry.is_regular_file() && entry.path().extension() == ".pchList")
        {
            pchlistFiles.push_back(entry.path());
        }
    }
    return pchlistFiles;
}

void sortPaths(std::vector<std::filesystem::path>& paths)
{
    std::sort(paths.begin(), paths.end(), [](const std::filesystem::path& a, const std::filesystem::path& b)
    {
        std::string nameA = a.stem().string();
        std::string nameB = b.stem().string();
        if (nameA.starts_with("PatchBank") && nameB.starts_with("PatchBank"))
        {
            int numberA = std::stoi(nameA.substr(9));
            int numberB = std::stoi(nameB.substr(9));
            return numberA < numberB;
        }
        return a.filename().string() < b.filename().string();
    });
}

int main(int argc, char** argv)
{
    try
    {
        Config config = parseArgs(argc, argv);
        if (config.sourceDirectory.empty() || config.destinationFile.empty())
        {
            throw std::runtime_error("Invalid arguments");
        }

        std::cout << "File listing:" << std::endl;
        auto pchlistFiles = findPchlistFiles(config.sourceDirectory);
        sortPaths(pchlistFiles);
        for (const std::filesystem::path& pchlistFile : pchlistFiles)
        {
            std::cout << pchlistFile << std::endl;
        }

        PchlistToReabankConverter converter;
        converter.convert(pchlistFiles, config.destinationFile);

        std::cout << "Conversion completed" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "(Type enter to terminate)" << std::endl;
    std::cin.get();
    return 0;
}
