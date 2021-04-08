#include "DataModel.h"
#include "CSVParser.h"

#include "InputFileTypes.h"

#include <QtCore/QVector>
#include <QtCore/QRandomGenerator>
#include <QtCore/QRect>
#include <QtGui/QColor>
#include <QSettings>
#include <iostream>


DataModel::DataModel(QObject* parent) :
    QAbstractTableModel(parent) {

    QSettings settings("Moose Soft", "Clipper");

    settings.beginGroup("Loader");
    //QString sText = "C:\\Fraps\\Benchmarks\\SC2_x64 2020-08-24 16-04-46-28 frametimes.csv";
    //settings.setValue("text", sText);

    QString sText = settings.value("text", "").toString();

    //loadData(sText.toStdString());
    settings.endGroup();
}

Series* DataModel::getSeries()
{
    return &seriesFrameData;
}


// Read a csv and load frame data
bool DataModel::loadData(const std::string fileName) {
    CSVParser parser;
    InputFileTypesProcessor processor;

    fname = QString(fileName.c_str());

    // Parse
    std::vector<Row> data = parser.parse(fileName);

    // Create a new series view
    seriesFrameData.setName("line1");
    seriesFrameData.setColor("cyan");

    // Find the input file the signature
    InputFileTypesProcessor::inputSig sig = processor.parse(fileName, data, frameData);
    
    // Update series data for plotting
    dataOffset = frameData[0].get()->startTime;
    for (auto& frame : frameData)
        seriesFrameData << QPointF(frame->startTime - dataOffset, frame->frameDuration);

    calcStats();
    return true;
}


int DataModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
        return frameData.size();
}

int DataModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
        return 2;
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section % 2 == 0)
            return "Frame#";
        else
            return "FrameTime";
    }
    else {
        return QString("%1").arg(section + 1);
    }
}

QVariant DataModel::data(const QModelIndex& index, int role) const
{
    if ((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        if (index.column() == 0) {
            return frameData[index.row()]->frameNum;
        }
        else if (index.column() == 1) {
            return frameData[index.row()]->frameDuration;
        }
        else return QVariant();

    }

    else if (role == Qt::BackgroundRole) {
        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

bool DataModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        if (index.column() == 0) {
            frameData[index.row()]->frameNum = value.toInt();
        }
        else if (index.column() == 1) {
            frameData[index.row()]->frameDuration = value.toDouble();
        }

        emit dataChanged(index, index);
        return true;
    }
    return false;
}


Qt::ItemFlags DataModel::flags(const QModelIndex& index) const
{
    return QAbstractItemModel::flags(index);
}

void DataModel::selected() {
    seriesFrameData.setColor("green");
}

void DataModel::unSelected() {
    seriesFrameData.setColor("white");
}


/*
void DataModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}

*/

void DataModel::calcStats()
{
    float totaltime = 0.0;
    int frames = 0;

    for (auto f : frameData) {
        totaltime += f->frameDuration;
        frames++;
    }

    stats.avg = frames / (totaltime / 1000.0);
}
