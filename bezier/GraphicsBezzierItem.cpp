#include "GraphicsBezzierItem.h"

GraphicsBezzierItem::GraphicsBezzierItem()
{

}

QRectF GraphicsBezzierItem::boundingRect() const {
    qreal penWidth = 1;
    // TODO
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                  20 + penWidth, 20 + penWidth);
}

void GraphicsBezzierItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget) {
    // TODO
    painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
}
