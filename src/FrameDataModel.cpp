#include "FrameDataModel.h"

#include <QtCore/QVector>
#include <QtCore/QRandomGenerator>
#include <QtCore/QRect>
#include <QtGui/QColor>
#include <iostream>

FrameDataModel::FrameDataModel(QObject* parent) :
    QAbstractTableModel(parent) {
}

// Access for datamodel
std::shared_ptr<DataModel> FrameDataModel::dataModel(int index)
{
    if (dataModels.size() > index)
        return dataModels[index];
    else
        return nullptr;
}

// Check for a valid filetype
bool FrameDataModel::validFile(const std::string& fileName)
{
    return true;
}

// Append data to the model
std::shared_ptr<DataModel>  FrameDataModel::addData(const std::string& fileName, bool dir)
{

    // Create a new datamodel and add to our store
    if (!dir) {

        std::shared_ptr<DataModel> dataModel = std::make_shared<DataModel>();

        if (dataModel->loadData(fileName)) {
    
            int row = dataModels.size();

            // Add to the vector of datamodels
            beginInsertRows(QModelIndex(), row, row);
            dataModels.push_back(dataModel);
            endInsertRows();

            return dataModel;
        }
    }

    return nullptr;
}

bool FrameDataModel::setModels(const std::vector<std::shared_ptr<DataModel>>& dataModels)
{
    this->dataModels = dataModels;
    return true;
}

int FrameDataModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
        return dataModels.size();
}

int FrameDataModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
        return 2;
}

QVariant FrameDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section % 2 == 0)
            return "Filename";
        else
            return "Directory";
    }
    else {
        return QString("%1").arg(section + 1);
    }
}

QVariant FrameDataModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return dataModels[index.row()]->fname;
    }
    else if (index.column() == 1) {
        return dataModels[index.row()]->stats.avg;
    }
    return QVariant();
}


bool FrameDataModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        if (dataModels.size() > index.row()) {
            dataModels[index.row()]->fname = value.toString();
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags FrameDataModel::flags(const QModelIndex& index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
