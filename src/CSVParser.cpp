#include "CSVParser.h"

#include <boost/regex.hpp>
#include <iostream>
#include <fstream>

CSVParser::CSVParser()
{
}

CSVParser::~CSVParser()
{
}

// used to split the file in lines
const boost::regex linesregx("\\r\\n|\\n\\r|\\n|\\r");

// used to split each line to tokens, assuming ',' as column separator
const boost::regex fieldsregx(",(?=(?:[^\"]*\"[^\"]*\")*(?![^\"]*\"))");


std::vector<Row> CSVParser::parse(const std::string filename, unsigned int size)
{
    std::vector<Row> result;

    // read example file
    std::ifstream infile;
    infile.open(filename);
    if (infile.fail()) {
        std::cout << "Failed Opening " << filename << " file for reading\n";
        return result;
    }

    // get length of file:
    infile.seekg(0, infile.end);
    int length = infile.tellg();
    infile.seekg(0, infile.beg);

    char* buffer = new char[length];
    
    //std::cout << "Reading " << length << " characters... ";
    
    // read data as a block:
    infile.read(buffer, length);

    /*if (infile)
        std::cout << "all characters read successfully.";
    else
        std::cout << "error: only " << infile.gcount() << " could be read";
    */

    infile.close();

    
    // iterator splits data to lines
    boost::cregex_token_iterator li(buffer, buffer + length, linesregx, -1);
    boost::cregex_token_iterator end;

    while (li != end) {
        std::string line = li->str();
        ++li;

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
    return result;
}
