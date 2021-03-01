#include "InputFileTypes.h"
#include "CSVParser.h"
#include <qdebug.h>
#include <iostream>
#include "Parsers.h"
#include <memory>
#include <QtCharts/QLineSeries>


InputFileTypesProcessor::InputFileTypesProcessor(QObject* parent) {
}

InputFileTypesProcessor::~InputFileTypesProcessor() {
}

InputFileTypesProcessor::inputSig InputFileTypesProcessor::parse(
    const std::string& fileName, 
    std::vector<Row>& rows, 
    std::vector<std::shared_ptr<Frame>>& frames, 
    Series& seriesFrameData) {

    // Check for input file sigs
    if (FrapsParser::sigMatch(rows[0])) {
        std::unique_ptr<Parser> parser = std::make_unique<FrapsParser>();
        rows.erase(rows.begin());
        if (parser->parseRows(fileName, rows, frames, seriesFrameData)) return parser->type();
    }

    else if (PresentMonParser::sigMatch(rows[0])) {
        std::unique_ptr<Parser> parser = std::make_unique<PresentMonParser>();
        if (parser->parseRows(fileName, rows, frames, seriesFrameData)) return parser->type();
    }

    return InputFileTypesProcessor::Error;
}


