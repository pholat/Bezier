#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
// So that we could actually hold whatever elements
#include <QAbstractGraphicsShapeItem>
#include <QTableWidgetItem>

class GraphicsScene : public QGraphicsScene
{
private:
    QVector<QAbstractGraphicsShapeItem*> bezierpoints;
    QVector<QPoint> getPoints();
    QVector<QGraphicsLineItem*> oldItems;
    QVector<QPoint> testpoints;

    void render();

    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0);
    ~GraphicsScene();
    void removePoint(const int pos);

signals:
    void AddPoint(QPoint pt);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void ChangePoint(QTableWidgetItem*);
private:
};

#endif // GRAPHICSSCENE_H
