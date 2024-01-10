#ifndef RANKING_H
#define RANKING_H

#include <QMainWindow>

namespace Ui {
class Ranking;
}

class Ranking : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ranking(QWidget *parent = nullptr);
    ~Ranking();

private:
    Ui::Ranking *ui;
};

#endif // RANKING_H
