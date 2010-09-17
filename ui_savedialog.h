/********************************************************************************
** Form generated from reading UI file 'savedialog.ui'
**
** Created: Mon 6. Sep 01:04:19 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEDIALOG_H
#define UI_SAVEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_savedialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *savedialog)
    {
        if (savedialog->objectName().isEmpty())
            savedialog->setObjectName(QString::fromUtf8("savedialog"));
        savedialog->resize(235, 90);
        savedialog->setMinimumSize(QSize(235, 90));
        savedialog->setMaximumSize(QSize(235, 90));
        verticalLayout = new QVBoxLayout(savedialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(savedialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(savedialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhLowercaseOnly|Qt::ImhUppercaseOnly);
        lineEdit->setMaxLength(32767);

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(savedialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(savedialog);

        QMetaObject::connectSlotsByName(savedialog);
    } // setupUi

    void retranslateUi(QDialog *savedialog)
    {
        savedialog->setWindowTitle(QApplication::translate("savedialog", "Save playlist", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("savedialog", "Enter playlist name:", 0, QApplication::UnicodeUTF8));
        lineEdit->setInputMask(QString());
    } // retranslateUi

};

namespace Ui {
    class savedialog: public Ui_savedialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEDIALOG_H
