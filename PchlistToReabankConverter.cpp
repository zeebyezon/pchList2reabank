// Created by David Bizon on 19/01/2025.

#include <iostream>
#include <fstream>
#include <sstream>
#include "PchlistToReabankConverter.h"

void PchlistToReabankConverter::convert(const std::vector<std::filesystem::path>& pchlistFiles, const std::filesystem::path& destinationFile)
{
    std::ofstream outputStream(destinationFile);
    if (!outputStream.is_open())
    {
        std::cerr << "Error: could not open destination file " << destinationFile << std::endl;
        return;
    }

    for (const std::filesystem::path& pchlistFile : pchlistFiles)
    {
        std::ifstream inputStream(pchlistFile);
        if (!inputStream.is_open())
        {
            std::cerr << "Error: could not open source file " << pchlistFile << std::endl;
            continue;
        }

        if (!convertPchlistFile(inputStream, outputStream))
        {
            throw std::runtime_error(pchlistFile.string() + ": unsupported file content");
        }
    }
}

bool PchlistToReabankConverter::convertPchlistFile(std::istream& inputContent, std::ostream& outputStream)
{
    std::string line;
    while (std::getline(inputContent, line))
    {
        if (line.empty())
        {
            continue;
        }

        if (line.starts_with("Version="))
        {
            if (line != "Version=Nord Modular G2 Bank Dump")
            {
                return false;
            }
            continue;
        }

        auto [bankNumber, programNumber, programName] = parseLine(line);
        if (bankNumber == -1)
        {
            return false;
        }

        if (bankNumber != m_currentBankNumber)
        {
            m_currentBankNumber = bankNumber;
            outputStream << "Bank 0 " << m_currentBankNumber << " " << (m_currentBankNumber + 1) << std::endl;
        }
        outputStream << programNumber << " " << programName << std::endl;
    }
    return true;
}

std::tuple<int, int, std::string> PchlistToReabankConverter::parseLine(const std::string& line)
{
    // Format: <BankNumber>:<ProgramNumber>: <ProgramName>.pch2

    auto end = line.find_last_of(".");
    if (end == std::string::npos)
    {
        return { -1, -1, "" };
    }

    std::stringstream lineStream(line.substr(0, end));
    int bankNumber = 0;
    lineStream >> bankNumber;
    lineStream.ignore(1);
    int programNumber = 0;
    lineStream >> programNumber;
    lineStream.ignore(2);
    std::string programName;
    std::getline(lineStream, programName);

    // Convert to 0-based index
    --bankNumber;
    --programNumber;

    return { bankNumber, programNumber, programName };
}
