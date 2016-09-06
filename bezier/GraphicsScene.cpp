#include "GraphicsScene.h"
#include <QDebug>

#include <QPainter>
#include "GraphicsBezzierItem.h"
#include <QtMath>

// My funs:

unsigned int fract(unsigned int val) {
    unsigned int tmp =1;
    for ( unsigned int i =2; i <= val; ++i ) {
        tmp = tmp*i;
    }
    return tmp;
}

float polynomialB(int i, int n, float u) {
    if(i < 0 || i > n)
        return 0;
    else {
        if(i == 0)
            return qPow(1-u, n);
        else
            return fract(n) * qPow(u, i) * qPow(1-u, n-i) / (fract(i) * fract(n-i));
    }
}

// void RysujKrzywa(SWezel *tablicaWezlow, int liczbaWezlow, TCanvas *Canvas) {
QVector<QLine> genBezierLinearAprox( QVector<QPoint> points, unsigned int weight = 1, float aprox = 0.005 ) {
    float x =0, y =0;
    QVector<QLine> retval;
    QPoint old = QPoint(points[0].x(),points[0].y());
    if ( points.size() > 2 ) {
        for(float u = 0; u <= 1; u += aprox )
        {
            float licznikX = 0;
            float licznikY = 0;
            float mianownik = 0;
            for(int i = 0; i < points.size(); i++) {
                licznikX += weight*points[i].x() * polynomialB(i, points.size()-1, u);
                licznikY += weight*points[i].y() * polynomialB(i, points.size()-1, u);
                mianownik+= weight * polynomialB(i, points.size()-1, u);
            }
            if(mianownik != 0) {
                x = licznikX/mianownik;
                y = licznikY/mianownik;
            } else {
                x = 0;
                y = 0;
            }
            retval.push_back(QLine(old,QPoint(x,y)));
            old = QPoint(x,y);
        }
    }
    return retval;
}

// ########################

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

GraphicsScene::~GraphicsScene()
{
    qDebug() << "deleted scene";
}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    static QVector<QPoint> testpoints;
    static QVector<QGraphicsLineItem*> oldItems;

      if ( mouseEvent->button() == Qt::LeftButton)
      {
          double rad = 1;
          QPointF pt = mouseEvent->scenePos();
          testpoints.push_back(QPoint(pt.x(),pt.y()));
          // TODO if I want to have it here.. I might want to save points coordinates too
          this->bezierpoints.append(
                      this->addEllipse( pt.x()-rad, pt.y()-rad, rad*4.0, rad*4.0,
                                        QPen(), QBrush(Qt::SolidPattern))
                  );
          // TODO remove old pick before new
          // for ( auto& val : testpoins ) {

          // gen bezier
          QVector<QLine> TT = genBezierLinearAprox( testpoints );

          // remove old lines
          for ( int i =0; i < oldItems.size(); ++i ) {
              this->removeItem(oldItems[i]);
          }
          oldItems.clear();

          // add new items on screen
          for ( int i =0; i < TT.size(); ++i ){
              oldItems.push_back( this->addLine(TT[i]) );
          }
      }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::removePoint(const int pos) {
    if ( pos < this->bezierpoints.size() ) {
        this->removeItem(this->bezierpoints[pos]);
        this->bezierpoints.remove(pos);
    }
}
