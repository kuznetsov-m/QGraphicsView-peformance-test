#include "form.h"
#include "ui_form.h"

#include <QLayout>
#include <QPainterPath>

#include <QRandomGenerator>
//#include <QDebug>
#include <QList>
#include <QObject>
#include <QMetaEnum>
#include <QGraphicsItem>
#include <time.h>

Q_DECLARE_METATYPE(QGraphicsItem::CacheMode)

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    qsrand(time_t(NULL));

    graphicsScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(graphicsScene);

    ui->cbGraphicsItemCacheMode->addItem("NoCache", QGraphicsItem::CacheMode::NoCache);
    ui->cbGraphicsItemCacheMode->addItem("ItemCoordinateCache", QGraphicsItem::CacheMode::ItemCoordinateCache);
    ui->cbGraphicsItemCacheMode->addItem("DeviceCoordinateCache", QGraphicsItem::CacheMode::DeviceCoordinateCache);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pb1_clicked()
{
//    auto graphicsPathItem = createGraphicsPathItem(QPointF(0,0), 4, 20, QGraphicsItem::CacheMode::NoCache);
//    graphicsScene->addItem(graphicsPathItem);
//----------------------
    auto line = new QGraphicsLineItem(0, 0, 0, -100);
    graphicsScene->addItem(line);
}

QGraphicsPathItem *Form::createGraphicsPathItem(const QPointF &pos,
                                                const int pointCount,
                                                const int maxSize,
                                                const QGraphicsItem::CacheMode &cacheMode)
{
    QPolygonF polygonF;

    // Формирование геометрии полигона
    for (int i = 0; i < pointCount; ++i) {
        const auto point = QPointF(
                    pos.x() + randomValue(-maxSize/2, maxSize/2),
                    pos.y() + randomValue(-maxSize/2, maxSize/2)
        );
        polygonF.append(point);
    }

    // Замкнуть полигон
    polygonF.append(polygonF.first());


    QPainterPath painterPath;
    painterPath.addPolygon(polygonF);


    auto graphicsPathItem = new QGraphicsPathItem();
    graphicsPathItem->setPath(painterPath);

    QBrush brush;
    brush.setColor(QColor(Qt::blue));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    graphicsPathItem->setBrush(brush);

    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(QColor(Qt::magenta));
    pen.setWidthF(1.);
    pen.setStyle(Qt::PenStyle::SolidLine);
    graphicsPathItem->setPen(pen);

    graphicsPathItem->setZValue(1);
    graphicsPathItem->setVisible(true);
    graphicsPathItem->update();
    graphicsPathItem->setPos(pos);
    //graphicsPathItem->setFlag();
    graphicsPathItem->setCacheMode(cacheMode);

    return graphicsPathItem;
}

void Form::on_pbCreate_clicked()
{
    for (int i = 0; i < ui->sbItemCount->value(); ++i) {
        const int min = -200;
        const int max = 200;
        const auto pos = QPointF(randomValue(min, max), randomValue(min, max));
        const auto pointCount = ui->sbItemPointCount->value();
        const auto maxSize = ui->sbItemMaxSize->value();
        const auto cacheMode = ui->cbGraphicsItemCacheMode->currentData().value<QGraphicsItem::CacheMode>();
        auto graphicsPathItem = createGraphicsPathItem(pos, pointCount, maxSize, cacheMode);
        graphicsScene->addItem(graphicsPathItem);
    }
}

int Form::randomValue(int min, int max)
{
    return qrand() % ((max + 1) - min) + min;
}

void Form::on_pbClear_clicked()
{
    graphicsScene->clear();
}

void Form::on_pbScalePlus_clicked()
{
    //QTransform mat
    //ui->graphicsView->setTransform();
    ui->graphicsView->setTransform(ui->graphicsView->transform().scale(1.1, 1.1));
}

void Form::on_pbScaleMinus_clicked()
{
    ui->graphicsView->setTransform(ui->graphicsView->transform().scale(0.9, 0.9));
}
