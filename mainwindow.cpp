#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "iostream"
#include "QGraphicsTextItem"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    QPen linhaPreta(Qt::black);
    linhaPreta.setWidth(1);

    scene->setSceneRect(-180, -90, 360, 180);
    ui->telaPlano->scale(1, -1);
    for(int i = -260; i<280; i=i+20)
    {

        scene->addLine(i,-280,i,280,linhaPreta);// VERTICAL
        scene->addLine(-280,i,280,i,linhaPreta);// HORIZONTAL
    }   
    ui->telaPlano->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//PARA RETA
void MainWindow::bresenham(int x0, int y0, int x1, int y1)
{
    QPen linhaVermelha(Qt::red);
    linhaVermelha.setWidth(3);
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    for(;;){
        scene->addEllipse((x0*20)-20,y0*20,20,20,linhaVermelha);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}
// ADAPTADO DE  https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C

// PARA CIRCULO
void MainWindow::drawCircle(int xc, int yc, int x, int y)
{
    QPen pontoAmarelo(Qt::blue);
    pontoAmarelo.setWidth(1);
    scene->addEllipse(xc+x*20, yc+y*20,20,20,pontoAmarelo);
    scene->addEllipse(xc-x*20, yc+y*20,20,20,pontoAmarelo);
    scene->addEllipse(xc+x*20, yc-y*20,20,20,pontoAmarelo);
    scene->addEllipse(xc-x*20, yc-y*20,20,20,pontoAmarelo);
    scene->addEllipse(xc+y*20, yc+x*20,20,20,pontoAmarelo);
    scene->addEllipse(xc-y*20, yc+x*20,20,20,pontoAmarelo);
    scene->addEllipse(xc+y*20, yc-x*20,20,20,pontoAmarelo);
    scene->addEllipse(xc-y*20, yc-x*20,20,20,pontoAmarelo);
}

void MainWindow::circleBres(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x)
    {
        drawCircle(xc, yc, x, y);
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y);
    }
}
//ADAPTADO DE http://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/

void MainWindow::on_actionIniciar_triggered()
{
    //ui->telaPlano->add
}

void MainWindow::on_pushButton_clicked()
{
    try{
        if(ui->coordenadaX->text().isEmpty()) throw
            QString("Campo de coordenada inicial X não pode ficar vazio!");
        if(ui->coordenadaY->text().isEmpty()) throw
            QString("Campo de coordenada inicial Y não pode ficar vazio!");
        if(ui->coordenadaXdestino->text().isEmpty()) throw
            QString("Campo de coordenada destino X não pode ficar vazio!");
        if(ui->coordenadaYdestino->text().isEmpty()) throw
            QString("Campo de coordenada destino Y não pode ficar vazio!");

        QPen linhaAzul(Qt::blue);
        linhaAzul.setWidth(3);
        int cordX = ui->coordenadaX->text().toInt();
        int cordY = ui->coordenadaY->text().toInt();
        int cordXDest = ui->coordenadaXdestino->text().toInt();
        int cordYDest = ui->coordenadaYdestino->text().toInt();
        scene->addLine(cordX*20-10,cordY*20+10,cordXDest*20-10,cordYDest*20+10,linhaAzul);
        setMouseTracking(true);
        // Bresenham
        bresenham(cordX,cordY,cordXDest,cordYDest);
        // pintar
        ui->telaPlano->setScene(scene);
    }
    catch(QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void MainWindow::on_btCirculo_clicked()
{
    try
    {
        if(ui->coordenadaXCirculo->text().isEmpty()) throw
            QString("Campo de coordenada X não pode ficar vazio!");
        if(ui->coordenadaYCirculo->text().isEmpty()) throw
            QString("Campo de coordenada  Y não pode ficar vazio!");
        if(ui->campoRaio->text().isEmpty()) throw
            QString("Campo de Raio não pode ficar vazio!");
        QPen circuloVerde(Qt::green);
        circuloVerde.setWidth(3);
        int cordX = ui->coordenadaXCirculo->text().toInt();
        int cordY = ui->coordenadaYCirculo->text().toInt();
        int raio = ui->campoRaio->text().toInt();
        raio = raio*20;
        scene->addEllipse((cordX*20)-raio,(cordY*20)-raio,raio*2,raio*2,circuloVerde);
        circleBres(cordX*20,cordY*20,raio/20);
        ui->telaPlano->setScene(scene);
    }
    catch(QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void MainWindow::on_actionLimpar_triggered()
{
    scene=new QGraphicsScene(this);
    QPen linhaPreta(Qt::black);
    linhaPreta.setWidth(1);

    scene->setSceneRect(-180, -90, 360, 180);
    ui->telaPlano->scale(1, -1);
    for(int i = -260; i<280; i=i+20)
    {
        scene->addLine(i,-280,i,280,linhaPreta);// VERTICAL
        scene->addLine(-280,i,280,i,linhaPreta);// HORIZONTAL
    }
    ui->telaPlano->setScene(scene);
}
