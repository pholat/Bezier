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
    QVector<QGraphicsLineItem*> oldItems;
    QVector<QPoint> testpoints;
    void render();

    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0);
    ~GraphicsScene();
    void removePoint(const int pos);
    const QVector<QPoint> getPoints() {
        return testpoints;
    }

signals:
    void AddPoint(QPoint pt);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void ModifyPoint(QTableWidgetItem*);
private:
};

#endif // GRAPHICSSCENE_H
