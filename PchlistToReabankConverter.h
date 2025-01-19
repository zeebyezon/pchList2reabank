// Created by David Bizon on 19/01/2025.
#pragma once

#include <vector>
#include <filesystem>

class PchlistToReabankConverter
{
public:
    PchlistToReabankConverter() = default;
    ~PchlistToReabankConverter() = default;
    PchlistToReabankConverter(const PchlistToReabankConverter&) = delete;
    PchlistToReabankConverter& operator=(const PchlistToReabankConverter&) = delete;
    PchlistToReabankConverter(PchlistToReabankConverter&&) = delete;
    PchlistToReabankConverter& operator=(PchlistToReabankConverter&&) = delete;

    void convert(const std::vector<std::filesystem::path>& pchlistFiles, const std::filesystem::path& destinationFile);

private:
    std::tuple<int, int, std::string> parseLine(const std::string& line);
    bool convertPchlistFile(std::istream& inputContent, std::ostream& outputStream);

private:
    int m_currentBankNumber = -1;
};
