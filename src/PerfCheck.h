#pragma once

#include "ui_PerfCheck.h"
#include <QtWidgets/QMainWindow>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include "FrameDataModel.h"

class DataModel;

class PerfCheck : public QMainWindow
{
    Q_OBJECT

public:
    PerfCheck(QWidget *parent = Q_NULLPTR);
    ~PerfCheck();
    bool setDataModels(std::vector < std::shared_ptr<DataModel>> &newDataModels);
    void closeEvent(QCloseEvent* event);
    void writeSettings();
    void readSettings();

private slots:
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);


private:

    // This local copy of refrences to datamodels
    FrameDataModel frameDataModel;

    Ui::PerfCheckClass ui;
    ChartView* chartView;
    QTableView* dataModelView;
    QTableView* listView;

    // One chart per perfcheck
    QValueAxis axisX;
    QValueAxis axisY;
    QChart chart;


private slots:
    void print_pressed();
    void datasetClicked(const QModelIndex& index);
};
