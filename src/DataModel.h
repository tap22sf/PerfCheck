#pragma once
#include <vector>

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>

#include "Frame.h"
#include "Series.h"


// Model for one dataset
class DataModel : public QAbstractTableModel
{
    Q_OBJECT


public:

    // Struct for statistics
    struct Stats {

        float avg;
        float _90thpercentile;
        float _95thpercentile;
        float _99thpercentile;

        float duration;
    };


    explicit DataModel(QObject* parent = 0);
    Series* getSeries();

    bool loadData(const std::string fileName);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex& index) const;

    QString fname;

    void selected();
    void unSelected();

    // Interface for statistics
    void calcStats();

    Stats stats;

private:

    // Raw data
    std::vector<std::shared_ptr<Frame>> frameData;

    // Offset of sample
    float dataOffset = 0;

    // Series data - used for graphs
    Series seriesFrameData;
};

