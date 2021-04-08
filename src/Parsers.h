#pragma once
//#include <QtCharts/QLineSeries>
#include "CSVParser.h"
#include "Frame.h"
#include "InputFileTypes.h"
#include <memory>
#include <map>


// Base class for parsers
class Parser
{
public:
    virtual bool parseRows(const std::string& fileName, const std::vector<Row>& rows, std::vector<std::shared_ptr<Frame>>& frames) = 0;
    virtual InputFileTypesProcessor::inputSig type() = 0;
};

// Base class for parsers
class FrapsParser : public Parser
{

public:
    bool static sigMatch(const Row& r);
    bool parseRows(const std::string& fileName, const std::vector<Row>& rows, std::vector<std::shared_ptr<Frame>>& frames) override;
    bool parseLine(const Row& r, std::shared_ptr<Frame>& frame);
    InputFileTypesProcessor::inputSig type() override { return InputFileTypesProcessor::FRAPS; }

private:
    qreal parserLastTime = 0;
    bool firstPass = true;
};

// Base class for parsers
class PresentMonParser : public Parser
{

public:
    bool static sigMatch(const Row& r);

    bool parseRows(const std::string& fileName, const std::vector<Row>& rows, std::vector<std::shared_ptr<Frame>>& frames) override;
    bool parseLine(const Row& r, std::shared_ptr<Frame>& frame);
    InputFileTypesProcessor::inputSig type() override { return InputFileTypesProcessor::PresentMon; }

private:
    qreal parserLastTime = 0;
    bool firstPass = true;
    std::map<std::string, int> fieldIndex;
};

