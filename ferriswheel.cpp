#include "ferriswheel.h"
#include <QPainter>
#include <cmath>

FerrisWheel::FerrisWheel(QWidget *parent)
    : QWidget(parent), angle(0), animationRunning(true)
{
    setFixedSize(450, 450);
    center = QPoint(width() / 2, height() / 2);
    radius = 150;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FerrisWheel::updateAnimation);
    timer->start(7);

    elapsedTimer.start();
}

void FerrisWheel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::DashLine);
    painter.setPen(pen);
    QPoint cabinTop = rotatePoint(QPoint(center.x(), center.y() + radius), angle);
    painter.drawLine(center, cabinTop);

    drawCabin(painter);
}

void FerrisWheel::updateAnimation()
{
    if (animationRunning)
    {
        qint64 elapsed = elapsedTimer.elapsed();
        elapsedTimer.restart();
        double deltaAngle = 360.0 * (elapsed / 1000.0) * (1.0 / 5.0);
        angle -= deltaAngle;
        if (angle <= -360.0) {
            angle = 0.0;
            animationRunning = false;
            timer->stop();
        }
        update();
    }
}

void FerrisWheel::drawCabin(QPainter &painter)
{
    QPoint cabinTop = rotatePoint(QPoint(center.x(), center.y() + radius), angle);
    QPoint triangleLeft(cabinTop.x() - 25, cabinTop.y() + 30);
    QPoint triangleRight(cabinTop.x() + 25, cabinTop.y() + 30);
    QPoint triangleBottom(cabinTop.x(), cabinTop.y() + 50);

    QPen pen(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawLine(cabinTop, triangleLeft);
    painter.drawLine(cabinTop, triangleRight);
    painter.drawLine(triangleLeft, triangleRight);

    QPoint rectBottomLeft(triangleLeft.x(), triangleLeft.y() + 30);
    QPoint rectBottomRight(triangleRight.x(), triangleRight.y() + 30);

    painter.drawLine(triangleLeft, rectBottomLeft);
    painter.drawLine(triangleRight, rectBottomRight);
    painter.drawLine(rectBottomLeft, rectBottomRight);
    //painter.drawLine(triangleLeft, triangleRight);

    pen.setWidth(2);
    painter.setPen(pen);
    int pointSize = 1;
    painter.drawLine(cabinTop.x() - pointSize, cabinTop.y() - pointSize, cabinTop.x() + pointSize, cabinTop.y() + pointSize);
    painter.drawLine(cabinTop.x() - pointSize, cabinTop.y() + pointSize, cabinTop.x() + pointSize, cabinTop.y() - pointSize);
}

QPoint FerrisWheel::rotatePoint(const QPoint &p, double angle)
{
    double radian = angle * M_PI / 180.0;
    int x = center.x() + (p.x() - center.x()) * cos(radian) - (p.y() - center.y()) * sin(radian);
    int y = center.y() + (p.x() - center.x()) * sin(radian) + (p.y() - center.y()) * cos(radian);
    return QPoint(x, y);
}
