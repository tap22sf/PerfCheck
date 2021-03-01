#pragma once
#include <QObject>
#include <memory>
#include <QtCharts/QLineSeries>

#include "CSVParser.h"
#include "Frame.h"
#include "Series.h"


class InputFileTypesProcessor : public QObject {

    Q_OBJECT
   
public:
    enum inputSig {
        None,
        FRAPS,
        PresentMon,
        Error
   };

public:
    InputFileTypesProcessor(QObject* parent = 0);
    ~InputFileTypesProcessor();
    InputFileTypesProcessor::inputSig parse(
        const std::string& fileName, std::vector<Row> &rows, std::vector<std::shared_ptr<Frame>>& frames, Series& seriesFrameData);

};
