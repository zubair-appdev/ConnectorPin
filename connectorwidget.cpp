#include "connectorwidget.h"
#include <QPainter>
#include <QDebug>
#include <QComboBox>
int ConnectorWidget::widgetCalled = 1;
QString first_combo,second_combo;
bool flag;



ConnectorWidget::ConnectorWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "class called"; // Debugging line

}



void ConnectorWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    qDebug() << "widgetCalled called: " << widgetCalled++;  // Debugging line
       QPainter painter(this);

       // Set up basic parameters
       int outerRadius = qMin(width(), height()) / 3 - 20;  // Radius for each circle
       int circleSpacing = outerRadius * 0.5;  // Space between left and right circles
       int pinRadius = outerRadius * 0.06;  // Adjusted for pin size

       // Define the positions of left and right circles
       QPoint leftCenter(width() / 4 - circleSpacing, height() / 2);
       QPoint rightCenter(3 * width() / 4 + circleSpacing, height() / 2);

       // Use user-provided data
       QList<int> ringPins = pinArray;  // User-entered pin counts
       QList<double> ringRadiusOffsets;
       for (float offset : floatArray) {
           ringRadiusOffsets.append(static_cast<double>(offset));  // Convert to double if needed
       }
       int extraRotateAngle = static_cast<int>(angleOfRotation);  // Use user-provided rotation angle

       qDebug() << pinArray << "pinArray from connectorWidget";
       qDebug() << floatArray << "floatArray from connectorWidget";
       qDebug() << angleOfRotation << "angleOfRotation from connectorWidget";
       qDebug() << totalPins << "totalPins from connectorWidget";


       QFont font = painter.font();
       font.setPointSize(pinRadius * 0.75);
       painter.setFont(font);

       QPoint centers[] = {leftCenter, rightCenter};

       QList<QPoint> pointsContainerLeft;
       QList<QPoint> pointsContainerRight;

       // Ensure we do not exceed the number of rings defined by the user
       int numberOfRings = qMin(ringPins.size(), ringRadiusOffsets.size());

       for (int circleIndex = 0; circleIndex < 2; ++circleIndex) {
           int pinCount = 0;
           QPoint center = centers[circleIndex];
           painter.drawEllipse(center, outerRadius, outerRadius);

           for (int ringIndex = 0; ringIndex < numberOfRings; ++ringIndex) {
               int ringPinCount = ringPins[ringIndex];
               double ringOffset = outerRadius * ringRadiusOffsets[ringIndex];

               for (int i = 0; i < ringPinCount; ++i) {
                   double angle = ((360.0 / ringPinCount) * i) - extraRotateAngle;
                   double radians = angle * (M_PI / 180.0);
                   int pinX = center.x() + (outerRadius - ringOffset) * cos(radians);
                   int pinY = center.y() + (outerRadius - ringOffset) * sin(radians);

                   if (circleIndex == 0) {
                       pointsContainerLeft.append(QPoint(pinX, pinY));
                   } else {
                       pointsContainerRight.append(QPoint(pinX, pinY));
                   }

                   painter.drawEllipse(QPoint(pinX, pinY), pinRadius, pinRadius);
                   QPoint textPosition(pinX - pinRadius * 0.5, pinY + pinRadius * 0.4);
                   painter.drawText(textPosition, QString::number(pinCount + 1));
                   pinCount++;
               }
           }
       }

    // Redraw all stored lines with their colors based on pin indices
    for (const ColoredLine &coloredLine : drawnLines) {
        painter.setPen(coloredLine.color);
        int leftIndex = coloredLine.startIndex;
        int rightIndex = coloredLine.endIndex;

        if (leftIndex < pointsContainerLeft.size() && rightIndex < pointsContainerRight.size()) {
            painter.drawLine(pointsContainerLeft[leftIndex], pointsContainerRight[rightIndex]);
        }
    }

    bool isNumeric1 = false;
    bool isNumeric2 = false;
    int firstCombo = first_combo.toInt(&isNumeric1) - 1;
    int secondCombo = second_combo.toInt(&isNumeric2) - 1;

    if (isNumeric1 && isNumeric2) {
        if (firstCombo >= 0 && firstCombo < pointsContainerLeft.size() &&
            secondCombo >= 0 && secondCombo < pointsContainerRight.size()) {
            QLine newLine(pointsContainerLeft[firstCombo], pointsContainerRight[secondCombo]);
            if (flag) {
                // Set the color based on the first combo box input
                int randomIndex = QRandomGenerator::global()->bounded(4);  // Generates a random index from 0 to 3
                QColor lineColor = colors[randomIndex];
                drawnLines.append(ColoredLine{firstCombo, secondCombo, lineColor});  // Store pin indices and color
                painter.setPen(lineColor); // Set the pen color
                painter.drawLine(newLine);  // Draw the new line
                qDebug() << "drawing from " + QString::number(firstCombo + 1) + " to " + QString::number(secondCombo + 1);
            }
        }
    }
}





