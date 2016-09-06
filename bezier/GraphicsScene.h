#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
// So that we could actually hold whatever elements
#include <QAbstractGraphicsShapeItem>

class GraphicsScene : public QGraphicsScene
{
private:
    QVector<QAbstractGraphicsShapeItem*> bezierpoints;

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
private:
};

#endif // GRAPHICSSCENE_H
