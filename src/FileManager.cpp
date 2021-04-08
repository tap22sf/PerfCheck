#include <iostream>
#include <memory>
#include <vector>

#include "TAPLib.h"
#include "MSG.h"

#include "FileManager.h"
#include "PerfCheck.h"
#include "FrameDataModel.h"

#include <QDrag>
#include <QSettings>
#include <QMimeData>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QItemSelectionModel>

// Slot for Print button
void FileManager::print_pressed() {
    //chartView->print();

    // Launch a child
}


void FileManager::addTestData() {

    fileListModel->addData(R"(C:\Users\TAPHome\Desktop\Particles 2021-03-20 10-17-04-82 frametimes.csv)", false);
}


FileManager::FileManager(QWidget* parent)
    : QMainWindow(parent)
{
    LogMessage("FileManager Created");

    setAcceptDrops(true);

    // Restore last settings
    readSettings();

    // Create the global strorage for all frame data
    fileListModel = std::make_unique<FrameDataModel>();

    ui.setupUi(this);
    statsTableView = ui.centralwidget->findChild<QTableView*>("StatsTable");
    fileTableView = ui.centralwidget->findChild<QTableView*>("FileTable");
    fileTableView->setModel(fileListModel.get());
    fileTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // Size columns
    fileTableView->setColumnWidth(0, 600);

    QTextEdit* msgPtr = ui.centralwidget->findChild<QTextEdit*>("msgPanel");
    myMSG::setMessagePanel(msgPtr);


    progressBar = ui.centralwidget->findChild<QProgressBar*>("progressBar");

    progressBar->setMaximum(100);
    progressBar->setMinimum(0);

    // Set up the progress bar signals
    connect(this, &FileManager::progressUpdate, this, &FileManager::updateProgress);

    emit(progressUpdate(0));

    addTestData();
}

void FileManager::updateProgress(int newValue)
{
    // Every 1000 events update UI
    if (newValue % 1000 == 0) {
        int pb = newValue / 1000 % 1000;
        progressBar->setValue(pb);
        QCoreApplication::processEvents();
    }
}

void FileManager::launch()
{
    launchSelected();
}

void FileManager::launchSelected()
{
    QItemSelectionModel* select = fileTableView->selectionModel();
    QModelIndexList selection = select->selectedRows(); // return selected row(s)

    std::vector < std::shared_ptr<DataModel>> selectedDataModels;

    // Multiple rows can be selected
    for (int i = 0; i < selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        std::shared_ptr<DataModel> d = fileListModel->dataModel(index.row());
        selectedDataModels.push_back(d);
    }

    // Launch a child
    std::shared_ptr<PerfCheck > pc = std::make_shared<PerfCheck>();
    pc->setDataModels(selectedDataModels);
    ws.push_back(pc);
    pc->show();
}

void FileManager::kill()
{
    // Kill oldest
    if (ws.size()) ws.erase(ws.begin());
}



// Save and restore settings
void FileManager::writeSettings()
{
    QSettings settings("TAPApp", "FileManager");

    settings.beginGroup("Loaded Items");
    settings.endGroup();

}

void FileManager::readSettings()
{
    QSettings settings("TAPApp", "FileManager");

    settings.beginGroup("Loaded Items");
    settings.endGroup();
}


// Given a URLlist add to the filelist model
void FileManager::addUrls(const QList<QUrl>& urlList)
{
    int cnt = 0;

    // extract the local paths of the files
    for (int i = 0; i < urlList.count(); ++i) {
        const QString& s = urlList[i].toLocalFile();
        QFileInfo check_file(s);
        QString n = check_file.filePath();
        bool dir = check_file.isDir();

        if (check_file.exists()) {
            fileListModel->addData(n.toStdString(), dir);
            emit(progressUpdate(++cnt));

            if (dir) {
                QDirIterator it(s, QStringList() << "*.csv", QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

                while (it.hasNext()) {
                    it.next();
                    QString n = it.fileInfo().filePath();
                    bool dir = it.fileInfo().isDir();
                    fileListModel->addData(n.toStdString(), dir);
                    emit(progressUpdate(++cnt));
                }
            }
        }
    }

    emit(progressUpdate(0));
}


// Allow enter if there is a URL
void FileManager::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}
void  FileManager::dropEvent(QDropEvent* event) {
    // Get the drop event info
    addUrls(event->mimeData()->urls());
}