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
    timer->start(16);

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
    QPoint cabinBottomLeft(cabinTop.x() - 25, cabinTop.y() + 30);
    QPoint cabinBottomRight(cabinTop.x() + 25, cabinTop.y() + 30);

    painter.setPen(Qt::SolidLine);
    painter.drawRect(cabinBottomLeft.x(), cabinBottomLeft.y(), 50, 30);

    QPoint triangleTip(cabinTop.x(), cabinTop.y() - 40);
    painter.drawLine(cabinTop, cabinBottomLeft);
    painter.drawLine(cabinTop, cabinBottomRight);
    painter.drawLine(cabinBottomLeft, cabinBottomRight);

    painter.setBrush(Qt::black);
    painter.drawEllipse(cabinTop, 2, 2);
}

QPoint FerrisWheel::rotatePoint(const QPoint &p, double angle)
{
    double radian = angle * M_PI / 180.0;
    int x = center.x() + (p.x() - center.x()) * cos(radian) - (p.y() - center.y()) * sin(radian);
    int y = center.y() + (p.x() - center.x()) * sin(radian) + (p.y() - center.y()) * cos(radian);
    return QPoint(x, y);
}
