#ifndef FARMOPOLIS_H
#define FARMOPOLIS_H

#include <QMainWindow>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class Farmopolis;
}

class Farmopolis : public QMainWindow
{
    Q_OBJECT

public:
    explicit Farmopolis(QWidget *parent = nullptr);
    ~Farmopolis();
    void groundlabelClicked(QLabel *label) ;
    bool eventFilter(QObject *obj, QEvent *event) ;
private slots:

    void on_buygroundpushButton_clicked();

    void on_buyhenpushButton_clicked();

private:
    Ui::Farmopolis *ui;
    QLabel *currentground = nullptr;

};

#endif // FARMOPOLIS_H
