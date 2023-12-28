#ifndef FARMOPOLIS_H
#define FARMOPOLIS_H

#include <QMainWindow>

namespace Ui {
class Farmopolis;
}

class Farmopolis : public QMainWindow
{
    Q_OBJECT

public:
    explicit Farmopolis(QWidget *parent = nullptr);
    ~Farmopolis();

private:
    Ui::Farmopolis *ui;
};

#endif // FARMOPOLIS_H
