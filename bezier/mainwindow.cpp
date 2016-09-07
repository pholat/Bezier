#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new GraphicsScene;


    QRectF exactRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->setSceneRect(exactRect);
    ui->graphicsView->setScene(scene);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);
    QStringList headers;
    headers << "X" << "Y";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    QObject::connect( scene, SIGNAL(AddPoint(QPoint)),                this,  SLOT(TablePointAdd(QPoint)) );
    QObject::connect( this,  SIGNAL(ValueChanged(QTableWidgetItem*)), scene, SLOT(ModifyPoint(QTableWidgetItem*) ));
    ui->scaleSpinBox->setValue(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_scaleSpinBox_valueChanged(double arg1)
{
    if ( arg1 > 0 ) {
        ui->graphicsView->scale(arg1, arg1);
    }
}

void MainWindow::TablePointAdd(QPoint pt)
{
    unsigned int supersizeme = 1;
    static int pos = 0;
    if ( ! (pos < ui->tableWidget->rowCount()) ) {
        ui->tableWidget->setRowCount( ui->tableWidget->rowCount() + supersizeme );
    }

    ui->tableWidget->setItem(pos, 0, new QTableWidgetItem( QString("%1").arg(pt.x())) );
    ui->tableWidget->setItem(pos, 1, new QTableWidgetItem( QString("%1").arg(pt.y())) );
    ++pos;
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    emit ValueChanged(item);
}

void MainWindow::on_tableWidget_entered(const QModelIndex &index)
{
    index.column();
}

void MainWindow::loadFileClicked() {
//    QString fileName = QFileDialog::getOpenFileName(FileName(this,
//        tr("Open Bezier data"), "/home/", tr("Bezier files (*.bz *.bez)"));
//    QFile tmp(fileName);
//    tmp.open( QFile::ReadOnly );
//    QTextStream inStream( &tmp);
//    // TODO read file here -> and trigger rendering
//    for ( QString t; t << inStream; ) {
//        QStringList t.split(",");
//    }
//    tmp.close();
}

void MainWindow::saveFileClicked() {
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Open Bezier data"), "/home/", tr("Bezier files (*.bz *.bez)"));
    QFile tmp(fileName);
    tmp.open( QFile::WriteOnly );
    QTextStream outStream( &tmp);
    QVector<QPoint> pts = scene->getPoints();
    outStream << "x,y\n";
    for ( int i =0; i < pts.size(); ++i ) {
        outStream << pts[i].x() << "," << pts[i].y() << "\n";
    }
    tmp.close();
}
