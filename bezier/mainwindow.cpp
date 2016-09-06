#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new GraphicsScene;


    QRectF exactRect(20, 10, 300, 200);
    ui->graphicsView->setSceneRect(exactRect);
    ui->graphicsView->setScene(scene);
    //    ui->graphicsView->setCenterOn(exactRect.center());

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(2);
    QStringList headers;
    headers << "X" << "Y" << "Z";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
//    TODO add on edit signall, right now - disable edit ...
//    QObject::connect(ui->graphicsView,SIGNAL(addPoint(QPoint)),
//                     ui->tableWidget, SLOT() );
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("1"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("2"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("3"));
// TODO enlarge table when new element added ...
    ui->scaleSpinBox->setValue(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_scaleSpinBox_valueChanged(double arg1) {
    if ( arg1 > 0 ) {
        ui->graphicsView->scale(arg1, arg1);
    }
}
