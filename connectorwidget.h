#ifndef CONNECTORWIDGET_H
#define CONNECTORWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <cmath>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QRandomGenerator>

#include <defines.h>

extern QString first_combo,second_combo;
extern bool flag;

struct ColoredLine {
    int startIndex;  // Index of the pin on the left side
    int endIndex;    // Index of the pin on the right side
    QColor color;    // Color of the line
};


class ConnectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectorWidget(QWidget *parent = nullptr);
    QList<ColoredLine> drawnLines;  // Correctly typed as QList<ColoredLine>


protected:
    void paintEvent(QPaintEvent *event) override;  // Paint event to draw the connector

private:
    static int widgetCalled;

    QColor colors[4] = {
        QColor(255, 0, 0),  // Bright Red
        QColor(0, 255, 0),  // Bright Green
        QColor(0, 0, 255),  // Bright Blue
        QColor(0, 0, 0)     // Black
    };
};

#endif // CONNECTORWIDGET_H
