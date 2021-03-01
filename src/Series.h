#pragma once
#include <QApplication>
#include <QLineSeries>


class Series : public QtCharts::QLineSeries {
public:
    Series(QObject* parent = nullptr) :
        QtCharts::QLineSeries(parent)
    {
        connect(this, &QtCharts::QXYSeries::clicked, this, &Series::onClicked);
    }

private slots:

    void onClicked() {

        // Create a new pen for the chart
        QPen p = pen();
        p.setWidth(p.width() + 2);
        setPen(p);
    }
};
