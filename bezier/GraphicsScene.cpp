#include "GraphicsScene.h"
#include <QDebug>

#include <QPainter>
#include <QtMath>

#include <vector>

// My funs:

unsigned int fract(unsigned int val)
{
    unsigned int tmp =1;
    for ( unsigned int i =2; i <= val; ++i ) {
        tmp = tmp*i;
    }
    return tmp;
}

float polynomialB(int i, int n, float u)
{
    if(i < 0 || i > n)
        return 0;
    else {
        if(i == 0)
            return qPow(1-u, n);
        else
            return fract(n) * qPow(u, i) * qPow(1-u, n-i) / (fract(i) * fract(n-i));
    }
}

// just for show
template < class A>
class MyList {
private:
    A *dataset;
    unsigned int increment;
    unsigned int size;
    unsigned int pos;
    void allocMem() {
        A *tmp = new A[size+increment];
        for ( unsigned int i =0; i < pos; ++i ) {
            *(tmp+1) = *(dataset+1);
        }
        delete[] dataset;
        dataset = tmp;
        size += increment;
    }

public:
    MyList() {
        increment = 1000;
        size = increment;
        pos = 0;
        dataset = new A[size];
    }

    ~MyList() {
        delete[] dataset;
    }

    A& operator[] (unsigned int val) {
        if ( val < pos ) {
            return dataset[val];
        }
    }

    MyList& push_back(A val) {
        if ( !( pos+1 < size) ) {
            allocMem();
        }
        dataset[pos] = val;
        pos++;
        return *this;
    }

    A* begin() {
        return dataset;
    }
    A* end() {
        return dataset+pos;
    }
};

// refactored and translated code from book
QVector<QLine> genBezierLinearAprox( QVector<QPoint> points, unsigned int weight = 1, float aprox = 0.005 )
{
    float x =0, y =0;
    MyList<QLine> retval;
    QPoint old = QPoint(points[0].x(),points[0].y());
    if ( points.size() > 2 ) {
        for(float u = 0; u <= 1; u += aprox ) {
            float numeratorX = 0, numeratorY = 0, denominator = 0;
            for(int i = 0; i < points.size(); i++) {
                numeratorX += weight*points[i].x() * polynomialB(i, points.size()-1, u);
                numeratorY += weight*points[i].y() * polynomialB(i, points.size()-1, u);
                denominator+= weight * polynomialB(i, points.size()-1, u);
            }
            if(denominator != 0) {
                x = numeratorX/denominator;
                y = numeratorY/denominator;
            } else {
                x = 0;
                y = 0;
            }
            retval.push_back(QLine(old,QPoint(x,y)));
            old = QPoint(x,y);
        }
    }
    return QVector<QLine>::fromStdVector(std::vector<QLine>(retval.begin(),retval.end()));
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
    if ( mouseEvent->button() == Qt::LeftButton) {
        double rad = 1;
        QPointF pt = mouseEvent->scenePos();

        testpoints.push_back(QPoint(pt.x(),pt.y()));
        emit this->AddPoint(QPoint(pt.x(),pt.y()));
        bezierpoints.push_back( this->addEllipse(  pt.x()-rad, pt.y()-rad, rad*4.0, rad*4.0,
                                QPen(), QBrush(Qt::SolidPattern))
                              );
        this->render();
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::render()
{
    QVector<QLine> TT = genBezierLinearAprox( testpoints );
    for ( int i =0; i < oldItems.size(); ++i ) {
        this->removeItem(oldItems[i]);
    }
    oldItems.clear();
    for ( int i =0; i < TT.size(); ++i ) {
        oldItems.push_back( this->addLine(TT[i]) );
    }
}

void GraphicsScene::removePoint(const int pos)
{
    // 1) get localisation
    // 2) remove from dataset
    // 3) remove from display
}

void GraphicsScene::ModifyPoint(QTableWidgetItem* it)
{
    double rad = 1;
    unsigned int newval = it->text().toInt();
    if ( !( it->row() < bezierpoints.size() ) ) {
        return; // This is when we actually add point not modify it...
    }
    QAbstractGraphicsShapeItem* el = bezierpoints[it->row()];

    // move elipse to propper point
    this->removeItem(el);
    if ( it->column() == 0 )
        el = this->addEllipse( newval-rad, el->y(), rad*4.0, rad*4.0,
                               QPen(), QBrush(Qt::SolidPattern));
    else
        el= this->addEllipse(  el->x(), newval-rad, rad*4.0, rad*4.0,
                               QPen(), QBrush(Qt::SolidPattern));

    // change value in old data
    if ( it->row() == 0) this->testpoints[it->column()].setX(newval);
    else                 this->testpoints[it->column()].setY(newval);
    // render
    render();
}
