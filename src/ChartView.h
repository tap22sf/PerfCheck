#pragma once

#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    ChartView(QWidget* parent = 0);
    void print();

protected:
    bool viewportEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

    void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE
    {
        qreal factor = event->angleDelta().y() > 0 ? 2.0 : 0.5;
        chart()->zoom(factor);
        event->accept();
        QChartView::wheelEvent(event);
    }

private:
    bool m_isTouching;
    QPointF m_lastMousePos;
};
