#pragma once

#include <vector>
#include <QtWidgets/QMainWindow>
#include "ui_FileManager.h"

#include "FrameDataModel.h"

class PerfCheck;

class FileManager : public QMainWindow
{
    Q_OBJECT

public:
    FileManager(QWidget *parent = Q_NULLPTR);

private:
    Ui::FileManagerClass ui;
    QTableView* statsTableView;
    QTableView* fileTableView; 
    QProgressBar* progressBar;

    // Current file list model
    std::unique_ptr<FrameDataModel> fileListModel;

    // Open windows for plots
    std::vector <std::shared_ptr<PerfCheck>> ws;

    void addUrls(const QList<QUrl>& urlList);
    void writeSettings();
    void readSettings();
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(const QDropEvent* event);

    void addTestData();

private slots:
    void print_pressed();
    void updateProgress(int newValue);
    void launchSelected();
    void kill();

signals:
    void progressUpdate(int newValue);

};
