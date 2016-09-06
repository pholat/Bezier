#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GraphicsScene.h"
#include "QGraphicsView"
#include "QGraphicsItem"
#include "QTableWidgetItem"

#include "QPoint"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_scaleSpinBox_valueChanged(double arg1);
    void TablePointAdd(QPoint);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_tableWidget_entered(const QModelIndex &index);

signals:
    void ValueChanged(QTableWidgetItem*);

private:
    Ui::MainWindow *ui;
    GraphicsScene *scene;
};

#endif // MAINWINDOW_H
