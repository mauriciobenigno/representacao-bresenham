#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgraphicsview.h>
#include <QMouseEvent>
#include <QEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionIniciar_triggered();

    //Bresenham
    void bresenham(int x1, int y1, int x2, int y2);
    //para circulo
    void drawCircle(int xc, int yc, int x, int y);
    void circleBres(int xc, int yc, int r);

    //botões
    void on_pushButton_clicked();
    void on_btCirculo_clicked();

    void on_actionLimpar_triggered();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

};

#endif // MAINWINDOW_H
