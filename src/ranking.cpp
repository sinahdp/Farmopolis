#include "ranking.h"
#include "ui_ranking.h"

#include <QFile>
#include <QTextStream>
#include "QString"

//database
#include <QSqlDatabase>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

Ranking::Ranking(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ranking)
{
    ui->setupUi(this);
    //set minmum size of page
    setMinimumSize(2000,1250);
    setMaximumSize(2000,1250);

    //add css file
    QFile styleFile(":/rec/Styles/FarmStyle.css");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&styleFile);
        QString style = stream.readAll();
        styleFile.close();
        this->setStyleSheet(style);
    }

    ui->rankingPlayerslabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    ui->titleRankinglabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    int numberOfRows ;
    QSqlQuery q;
    q.prepare("SELECT MAX(CAST(id AS INTEGER)) FROM managers");  // جایگزین کردن "id" با نام فیلد مورد نظر شما
    if (q.exec() && q.next()) {
        int maxId = q.value(0).toInt();
        numberOfRows = maxId ;
    }

    QSqlQuery query("SELECT username, coins FROM managers ORDER BY coins DESC");

    for (int row = 2; row <= numberOfRows + 1 && query.next(); ++row) {
        for (int col = 0; col < 3; ++col) {
            if(col == 0) {
                QLabel *rankLabel = new QLabel(QString("  %1").arg(row - 1));
                rankLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
                ui->rankinggridLayout->addWidget(rankLabel, row, col);
            }
            else if(col == 1) {
                QString username = query.value(0).toString();
                QLabel *usernameLabel = new QLabel(username);
                usernameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
                ui->rankinggridLayout->addWidget(usernameLabel, row, col);
            }
            else if(col == 2) {
                int coins = query.value(1).toInt();
                QLabel *coinsLabel = new QLabel(QString("  %1").arg(coins));
                coinsLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
                ui->rankinggridLayout->addWidget(coinsLabel, row, col);
            }
        }
    }
}

Ranking::~Ranking()
{
    delete ui;
}
