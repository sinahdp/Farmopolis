#include "farmopolis.h"
#include "ui_farmopolis.h"

//file
#include <QFile>
#include <QTextStream>
#include "QString"

#include <QMouseEvent>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

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

    // Create a new QGridLayout and add it to the graphics view
    QGridLayout *gridLayout = new QGridLayout(ui->groundwidget);
    const int numRows = 4;
    const int numCols = 5;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            QLabel *square = new QLabel(ui->groundwidget);
            gridLayout->addWidget(square, i, j);
        }
    }

    QList<QLabel *> labelList = ui->groundwidget->findChildren<QLabel *>();
    for (QLabel *label : labelList) {
        label->installEventFilter(this);
    }
}

Farmopolis::~Farmopolis() {
    delete ui;
}

bool Farmopolis::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QLabel *clickedLabel = qobject_cast<QLabel *>(obj);
        if (clickedLabel) {
            QString originalStyles = clickedLabel->styleSheet();
            clickedLabel->setStyleSheet(originalStyles + "border:3px solid #212529;") ;
            if(currentground) {
                QString originalStyles = currentground->styleSheet();
                currentground->setStyleSheet(originalStyles + "border:3px solid #FFB703;") ;
            }
            currentground = clickedLabel ;
        }
    }
    return QObject::eventFilter(obj, event);
}

void Farmopolis::on_buygroundpushButton_clicked() {
    if (currentground && !currentground->styleSheet().contains("#55A630")) {
        currentground->setStyleSheet("background-color: #55A630; border:3px solid #212529;");
    }
}



void Farmopolis::on_buyhenpushButton_clicked()
{
    if (currentground && currentground->styleSheet().contains("#55A630")) {
        QString originalStyles = currentground->styleSheet();
        currentground->setStyleSheet("background: #55A630 url(:/rec/Icons/farm/hen.png) no-repeat;");
    }
}

