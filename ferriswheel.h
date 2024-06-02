#ifndef FERRISWHEEL_H
#define FERRISWHEEL_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>

class FerrisWheel : public QWidget
{
    Q_OBJECT

public:
    FerrisWheel(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateAnimation();

private:
    void drawCabin(QPainter &painter);
    QPoint rotatePoint(const QPoint &p, double angle);

    QTimer *timer;
    QElapsedTimer elapsedTimer;
    double angle;
    QPoint center;
    int radius;
    bool animationRunning;
};

#endif // FERRISWHEEL_H
