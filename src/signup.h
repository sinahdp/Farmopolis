#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>

#include <QLabel>
#include <QLineEdit>

#include <QMediaPlayer>

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
    void setFormNumber() ;
    void hidelabels() ;
    void hideBorderlineEdits() ;

    bool checlen(QString str) ;

    bool checkbadstr(QString str) ;

    bool endcheck(QString str) ;

    void generateCaptcha(QLabel *captchaLabel) ;

    void checkCaptcha(QLineEdit *captchaEntry , QLabel *captchaLabel , QLabel *erorLable) ;

    int NumberOfUsers ;
private slots:

    void on_boxpushButton_clicked();

    void on_hidepasswordpushButton_clicked();

    void on_generatecapchapushButton_clicked();

    void on_submitAndNextpushButton_clicked();

    void on_passlineEdit_textChanged(const QString &arg1);

    void on_emaillineEdit_textChanged(const QString &arg1);

    void on_bankassetlineEdit_textChanged(const QString &arg1);

    void on_boxlineEdit_textChanged(const QString &arg1);

    void on_phonenumberlineEdit_textChanged(const QString &arg1);

    void on_userlineEdit_textChanged(const QString &arg1);

    void on_darkmodepushButton_clicked();

private:
    Ui::SignUp *ui;
};
#endif // SIGNUP_H
