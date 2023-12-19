#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SignUp; }
QT_END_NAMESPACE

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    SignUp(QWidget *parent = nullptr);
    ~SignUp();

    //fade animation
    void fadeAnimation() ;
    void emptyTheForm() ;
    void settingFormNumber() ;

private slots:

    void on_nextpushButton_clicked();

    void on_previouspushButton_clicked();

    void on_boxpushButton_clicked();


private:
    Ui::SignUp *ui;
};
#endif // SIGNUP_H
