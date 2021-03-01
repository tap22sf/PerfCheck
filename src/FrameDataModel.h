#pragma once

#include <QtCore/QAbstractTableModel>
#include "DataModel.h"

// This class holds all of the current loaded data and acts as a tablemodel for the file list view
class FrameDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    FrameDataModel(QObject* parent = 0);
    std::shared_ptr<DataModel> dataModel(int index);
    bool validFile(const std::string& fileName);

    std::shared_ptr<DataModel> addData(const std::string& fileName, bool dir);
    bool setModels(const std::vector<std::shared_ptr<DataModel>>& dataModels);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex& index) const;

    // Keep all the data in here
    std::vector<std::shared_ptr<DataModel>> dataModels;
};
