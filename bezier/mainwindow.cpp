#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new GraphicsScene;


    QRectF exactRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->setSceneRect(exactRect);
    ui->graphicsView->setScene(scene);
    //    ui->graphicsView->setCenterOn(exactRect.center());

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);
    QStringList headers;
    headers << "X" << "Y";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    QObject::connect( scene, SIGNAL(AddPoint(QPoint)),                this,  SLOT(TablePointAdd(QPoint)) );
    QObject::connect( this,  SIGNAL(ValueChanged(QTableWidgetItem*)), scene, SLOT(ChangePoint(QTableWidgetItem*) ));
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
    // TODO this is bad... spank spank spank bad programmer
    unsigned int supersizeme = 1;
    static unsigned int pos = 0;
    if ( ! (pos < ui->tableWidget->rowCount()) ) {
        ui->tableWidget->setRowCount( ui->tableWidget->rowCount() + supersizeme );
    }

    qDebug("Point: %d :: %d :: ", pt.x(), pt.y() );

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
}
