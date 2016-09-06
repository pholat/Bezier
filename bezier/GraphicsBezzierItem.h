#ifndef GRAPHICSBEZZIERITEM_H
#define GRAPHICSBEZZIERITEM_H


#include <QPainter>
#include <QGraphicsItem>

class GraphicsBezzierItem : public QGraphicsItem
{
public:
    GraphicsBezzierItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHICSBEZZIERITEM_H
