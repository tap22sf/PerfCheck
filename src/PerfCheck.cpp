#include <iostream>

#include "PerfCheck.h"
#include "RandomData.h"
#include "DataModel.h"
#include "FrameDataModel.h"

#include <QSettings>
#include <QtWidgets/QTableView>
#include <QtWidgets/QListView>

#include <qdebug.h>
#include "chartview.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QStackedLayout>
#include <QTextStream>
#include <QHeaderView>

PerfCheck::PerfCheck(QWidget* parent)
    : QMainWindow(parent) {

    std::cout << "Created PerfCheck" << std::endl;

    ui.setupUi(this);
    readSettings();

    QFrame* frame = new QFrame(ui.centralWidget);
    ui.statsLayout->addWidget(frame);

    // Grab key views from the UI
    chartView = ui.centralWidget->findChild<ChartView*>();
    dataModelView = ui.centralWidget->findChild<QTableView*>("dataTable");
    listView = ui.centralWidget->findChild<QTableView*>("fileTable");

    listView->setModel(&frameDataModel);
    listView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Set up tableView
    dataModelView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dataModelView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Setup a chart
    chart.setTheme(QChart::ChartThemeDark);
    chart.setTitle("FrameViewer");
    chart.setDropShadowEnabled(false);
    chart.legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    //chart.legend()->hide();

    // Assign chart to chartview
    chartView->setChart(&chart);

    // Setup chart Axes
    axisX.setTitleText("Time(ms)");
    axisX.setTickAnchor(0);
    //axisX->setTickCount(10);
    axisX.applyNiceNumbers();
    chart.addAxis(&axisX, Qt::AlignBottom);

    axisY.setTitleText("FrameTime(ms)");
    axisY.setRange(0, 50);
    //axisY->setTickCount(10);
    axisY.applyNiceNumbers();
    chart.addAxis(&axisY, Qt::AlignLeft);

    connect(listView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
        this,
        SLOT(selectionChanged(const QItemSelection&, const QItemSelection&)));
}
void PerfCheck::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{

    // Unsleect all
    for (auto d : frameDataModel.dataModels)
        d->unSelected();


    std::cout << "Selected" << std::endl;
    for (auto& index : selected.indexes()) {
        std::cout << "   Row  : " << index.row() << std::endl;

        std::shared_ptr<DataModel> dataModel = frameDataModel.dataModel(index.row());
        std::cout << "   File : " << dataModel->fname.toStdString() << std::endl;

        dataModel->selected();
        dataModelView->setModel(dataModel.get());
    }
}

bool PerfCheck::setDataModels(std::vector < std::shared_ptr<DataModel>> &newDataModels) {
    frameDataModel.setModels(newDataModels);
    
    for (auto dataModel : newDataModels) {

        dataModelView->setModel(dataModel.get());

        // Add the series to the chart
        auto s = dataModel->getSeries();
        chart.addSeries(s);
        s->attachAxis(&axisY);
        s->attachAxis(&axisX);
    }
    return false;
}

// Save and restore settings
void PerfCheck::writeSettings() {
    QSettings settings("Moose Soft", "Clipper");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void PerfCheck::readSettings() {
    QSettings settings("Moose Soft", "Clipper");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void PerfCheck::datasetClicked(const QModelIndex& index) {
    std::string d = frameDataModel.data(index).toString().toStdString();

    /*
    std::shared_ptr<DataModel> dataModel = dataModels[index.row()];
    //std::cout << dataModel->fname.toStdString() <<  std::endl;

    // Unsleect all
    for (auto d : dataModels)
        d->unSelected();

    dataModel->selected();
    dataModelView->setModel(dataModel.get());
    */

}


// Slot for Print button
void PerfCheck::print_pressed() {
    chartView->print();
}

PerfCheck::~PerfCheck() {
    std::cout << "Destroyed PerfCheck" << std::endl;
}

void PerfCheck::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}
