#include "dialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

void Dialog::initUi()
{
    checkBoxUnderline = new QCheckBox(tr("UnderLine"));
    checkBoxItalic = new QCheckBox(tr("Italic"));
    checkBoxBold = new QCheckBox(tr("Bold"));

    QHBoxLayout *HLayout1 = new QHBoxLayout;
    HLayout1->addWidget(checkBoxUnderline);
    HLayout1->addWidget(checkBoxItalic);
    HLayout1->addWidget(checkBoxBold);

    radioButtonBlue = new QRadioButton("Blue");
    radioButtonRad = new QRadioButton("Rad");
    radioButtonBlack = new QRadioButton("Blank");

    QHBoxLayout *HLayout2 = new QHBoxLayout;
    HLayout2->addWidget(radioButtonBlue);
    HLayout2->addWidget(radioButtonRad);
    HLayout2->addWidget(radioButtonBlack);


    plainTextEdit = new QPlainTextEdit;
    QFont font = plainTextEdit->font();
    font.setPointSize(14);
    plainTextEdit->setFont(font);
    plainTextEdit->setPlainText("Hello World!\nLKC CG!");


    btnOk = new QPushButton("OK");
    btnCancel = new QPushButton("Cancel");
    btnQuit = new QPushButton("Quit");

    QHBoxLayout *HLayout3 = new QHBoxLayout;
    HLayout3->addStretch();
    HLayout3->addWidget(btnOk);
    HLayout3->addWidget(btnCancel);
    HLayout3->addStretch();
    HLayout3->addWidget(btnQuit);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addLayout(HLayout1);
    VLayout->addLayout(HLayout2);
    VLayout->addWidget(plainTextEdit);
    VLayout->addLayout(HLayout3);
    setLayout(VLayout);
}

void Dialog::initSignalSlots()
{
    connect(btnOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnQuit, SIGNAL(clicked()), this, SLOT(close()));

    /*
    clicked和槽函数on_checkUnderline后面的bool，要么全都有，要么全都没有，如果只有一个，信号与槽函数不起作用
    这是因为 Qt 的信号与槽连接需要参数类型和数量保持一致。如果参数类型和数量不匹配，连接可能会失效，信号无法正确触发槽函数。
    */
    connect(checkBoxUnderline, SIGNAL(clicked(bool)), this, SLOT(on_checkUnderline(bool)));
    connect(checkBoxItalic, SIGNAL(clicked(bool)), this, SLOT(on_checkItalic(bool)));
    connect(checkBoxBold, SIGNAL(clicked(bool)), this, SLOT(on_checkBold(bool)));

    connect(radioButtonBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(radioButtonRad, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(radioButtonBlack, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
}

void Dialog::on_checkUnderline(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setUnderline(checked);
    plainTextEdit->setFont(font);
}

void Dialog::on_checkItalic(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setItalic(checked);
    plainTextEdit->setFont(font);
}

void Dialog::on_checkBold(bool checked)
{
    QFont font = plainTextEdit->font();
    font.setBold(checked);
    plainTextEdit->setFont(font);
}

void Dialog::setTextFontColor()
{
    QPalette plet = plainTextEdit->palette();
    if(radioButtonBlue->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::blue);
    }
    else if (radioButtonRad->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::red);
    }
    else if (radioButtonBlack->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::black);
    }
    else
    {
        plet.setColor(QPalette::Text, Qt::black);
    }
    plainTextEdit->setPalette(plet);
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    initUi();
    initSignalSlots();
}

Dialog::~Dialog()
{
}

