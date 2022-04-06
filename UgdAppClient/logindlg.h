#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

namespace Ui {
class LoginDlg;
}
//��¼����
//1.���ӷ�����
//2.��֤�û���������
class CTcpClient;
class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(CTcpClient *pTcpClient,QWidget *parent = nullptr);
    ~LoginDlg();
    void closeEvent(QCloseEvent *);

private slots:
    void on_CancelBtn_clicked();

    void on_LoginBtn_clicked();

private:
    Ui::LoginDlg *ui;
    CTcpClient *m_tcpClient;
    bool m_bImmediatelyCancel; //����ȡ��
};

#endif // LOGINDLG_H
