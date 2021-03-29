#include "CSVParser.h"
#include "TAPLib.h"
#include "MSG.h"

#include <boost/regex.hpp>
#include <iostream>
#include <fstream>

CSVParser::CSVParser()
{
}

CSVParser::~CSVParser()
{
}

// used to split each line to tokens, assuming ',' as column separator
const boost::regex fieldsregx(",(?=(?:[^\"]*\"[^\"]*\")*(?![^\"]*\"))");

std::vector<Row> CSVParser::parse(const std::string filename)
{
    InfoMessage("Parsing : " + filename);

    std::vector<Row> result;

    // read example file
    std::ifstream infile;
    infile.open(filename);
    if (infile.is_open())
    {
        std::string line;
        while (std::getline(infile, line)) {

            // Split line to tokens
            boost::sregex_token_iterator ti(line.begin(), line.end(), fieldsregx, -1);
            boost::sregex_token_iterator end2;

            std::vector<std::string> row;
            while (ti != end2) {
                std::string token = ti->str();
                ++ti;
                row.push_back(token);
            }
            if (line.back() == ',') {
                // last character was a separator
                row.push_back("");
            }
            result.push_back(row);
        }

        infile.close();
    }

    else {
        LogMessage ("Failed Opening : " +  filename + " file for reading");
    }

    return result;
}
