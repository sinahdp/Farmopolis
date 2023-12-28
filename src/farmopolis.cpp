#include "farmopolis.h"
#include "ui_farmopolis.h"

//graphics view
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QHBoxLayout>

//file
#include <QFile>
#include <QTextStream>
#include "QString"

Farmopolis::Farmopolis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Farmopolis)
{
    ui->setupUi(this);

    //set minmum size of page
    setMinimumSize(2000,1200);
    setMaximumSize(2000,1200);

    //add css file
    QFile styleFile(":/rec/Styles/FarmStyle.css");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&styleFile);
        QString style = stream.readAll();
        styleFile.close();
        this->setStyleSheet(style);
    }

}

Farmopolis::~Farmopolis()
{
    delete ui;
}
