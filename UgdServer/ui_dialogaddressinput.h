/********************************************************************************
** Form generated from reading UI file 'dialogaddressinput.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDRESSINPUT_H
#define UI_DIALOGADDRESSINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogAddressInput
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_addr;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *lineEdit_port;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogAddressInput)
    {
        if (DialogAddressInput->objectName().isEmpty())
            DialogAddressInput->setObjectName(QString::fromUtf8("DialogAddressInput"));
        DialogAddressInput->resize(184, 106);
        verticalLayout = new QVBoxLayout(DialogAddressInput);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(DialogAddressInput);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEdit_addr = new QLineEdit(DialogAddressInput);
        lineEdit_addr->setObjectName(QString::fromUtf8("lineEdit_addr"));

        horizontalLayout->addWidget(lineEdit_addr);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(DialogAddressInput);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_port = new QLineEdit(DialogAddressInput);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));

        horizontalLayout_2->addWidget(lineEdit_port);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(DialogAddressInput);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogAddressInput);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogAddressInput, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogAddressInput, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogAddressInput);
    } // setupUi

    void retranslateUi(QDialog *DialogAddressInput)
    {
        DialogAddressInput->setWindowTitle(QApplication::translate("DialogAddressInput", "Participate in CLUSTER", nullptr));
        label_3->setText(QApplication::translate("DialogAddressInput", "Addr", nullptr));
        label_4->setText(QApplication::translate("DialogAddressInput", "Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogAddressInput: public Ui_DialogAddressInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDRESSINPUT_H
