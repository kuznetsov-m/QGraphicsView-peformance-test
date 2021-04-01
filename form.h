#pragma once

#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsPathItem>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pb1_clicked();

    void on_pbCreate_clicked();

    void on_pbClear_clicked();

    void on_pbScalePlus_clicked();

    void on_pbScaleMinus_clicked();

private:
    Ui::Form *ui;

    QGraphicsScene *graphicsScene = nullptr;

    QGraphicsPathItem *createGraphicsPathItem(const QPointF &pos,
                                              const int pointCount,
                                              const int maxSize,
                                              const QGraphicsItem::CacheMode &cacheMode);

    int randomValue(int min, int max);
};
