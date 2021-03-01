#include "FileManager.h"
#include <QtWidgets/QApplication>
#include "PerfCheckVersion.h"
#include "TAPLib.h"
#include <sstream>
#include <iostream>

int main(int argc, char *argv[])
{
    // report version
    std::stringstream oss;

    oss << argv[0] << " Version " << PerfCheck_VERSION_MAJOR << "."
                                  << PerfCheck_VERSION_MINOR;
    LogMessage(oss.str());
    
    /*TAPLib::Timer Timer("First");
    for (int i = 0; i < 5; i++) {

        float y = 0;
        for (int j = 0; j < 4*100000000; j++) {
            y = y + 1;
        }

        LogMessage(Timer.Print());
    }
    */
    LogMessage("App Started.");
    QApplication a(argc, argv);
    FileManager w;
    w.show();
    return a.exec();
}