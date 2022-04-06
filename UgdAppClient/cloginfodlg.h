#ifndef CLOGINFODLG_H
#define CLOGINFODLG_H

#include <QDialog>
#include "st_message.h"

namespace Ui {
class CLogInfoDlg;
}

using namespace BdUgdServer;
class CTcpClient;
class CLogInfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CLogInfoDlg(CTcpClient *pTcpClient,QWidget *parent = nullptr);
    ~CLogInfoDlg();
    void setProductsName(const QStringList &names);

private slots:
    void on_QueryLogBtn_clicked();

    void on_AddLogBtn_clicked();

    void on_TurningLeftBtn_clicked();

    void on_TurningRightBtn_clicked();

    void on_BackBtn_clicked();

    void on_MoreBtn_clicked();

    void on_ContentIndexCbx_currentIndexChanged(int index);

    void on_StartDateTimeBtn_clicked();

    void on_EndDateTimeBtn_clicked();

    void on_LogTypeCmbx_currentIndexChanged(int index);

    void on_LogTypeCmbxT_currentIndexChanged(int index);

private:
    void queryLogs();
    void updateData(const QList<BD_REQUEST_LOG_S> &infos);
    void showEvent(QShowEvent *);

private:
    struct page_info{
        int total_size; //��Ŀ����
        int page_no;    //ҳ��
        int page_size;  //ҳ��С
        int pages;      //��ҳ��
        int first_page; //��һҳ
        int last_page;  //���һҳ
    }m_pageInfo;
    Ui::CLogInfoDlg *ui;
    CTcpClient * m_tcpClient;
    bool m_isLoading; //�Ƿ����ڼ�������
    QString m_dateTimeFormat;
    QStringList m_logTypes;
    QStringList m_logSubtypes;
    QStringList m_resultTypes;
    QStringList m_upgradeTypes;
    QStringList m_devModuleTypes;
    QStringList m_devModuleStatusTypes;
    QStringList m_statusTypes;

};

#endif // CLOGINFODLG_H
