/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <iostream>
#include "chartview.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QApplication>
#include <QPrinter>
#include <QPrintDialog>

ChartView::ChartView(QWidget* parent):
    QChartView(parent),
    m_isTouching(false) {

    setDragMode(QGraphicsView::NoDrag);
    setMouseTracking(true);
    setRubberBand(QChartView::HorizontalRubberBand);
    setRenderHint(QPainter::Antialiasing);

}

void ChartView::print()
{

    QPrinter* printer = new QPrinter();
    printer->setOrientation(QPrinter::Landscape);
    printer->setResolution(QPrinter::HighResolution);

    QPrintDialog* dialog = new QPrintDialog(printer);
    dialog->setWindowTitle("Print Plots");
    if (dialog->exec() != QDialog::Accepted)
        return;
    QPainter* painter = new QPainter();
    painter->begin(printer);
    render(painter);

    painter->end();
    delete(dialog);
    delete(painter);
    delete(printer);
}


bool ChartView::viewportEvent(QEvent* event)
{
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
        m_lastMousePos = event->pos();
        event->accept();
    }

    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent* event) {

    // pan the chart with a middle mouse drag
        // pan the chart with a middle mouse drag
    if (event->buttons() & Qt::MiddleButton)
    {
        auto dPos = event->pos() - m_lastMousePos;
        chart()->scroll(-dPos.x(), dPos.y());

        m_lastMousePos = event->pos();
        event->accept();

    }

    if (m_isTouching)
        return;
    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent* event)
{
    QApplication::restoreOverrideCursor();

    if (m_isTouching)
        m_isTouching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
    //chart()->setAnimationOptions(QChart::SeriesAnimations);

    QChartView::mouseReleaseEvent(event);
}

void ChartView::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;

    case Qt::Key_F:
        chart()->zoomReset();
        chart()->zoomIn();
        chart()->zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}



