
#include "SettingsWindow.h"
#include<QDebug>
SettingsWindow::SettingsWindow(QWidget* parent)
    : QWidget(parent)
{
    // 设置窗口的布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    // 并口地址输入
    layout->addWidget(new QLabel("Port Address :"));
    m_portAddressEdit = new QLineEdit("8888", this);
    m_portAddressEdit->setValidator(new QRegExpValidator(QRegExp("^0x[0-9A-Fa-f]{1,4}$"), this));
    layout->addWidget(m_portAddressEdit);
    // 闪烁间隔
    layout->addWidget(new QLabel("Flash Interval (ms):"));
    m_flashIntervalEdit = new QLineEdit("500",this);
    m_flashIntervalEdit->setValidator(new QIntValidator(1, 10000, this));
    layout->addWidget(m_flashIntervalEdit);

    // 闪烁持续时间
    layout->addWidget(new QLabel("Flash Duration (ms):"));
    m_flashDurationEdit = new QLineEdit("500",this);
    m_flashDurationEdit->setValidator(new QIntValidator(1, 10000, this));
    layout->addWidget(m_flashDurationEdit);

    // 最大闪烁次数
    layout->addWidget(new QLabel("Max Flashes:"));
    m_maxFlashesEdit = new QLineEdit("120",this);
    m_maxFlashesEdit->setValidator(new QIntValidator(1, 10000, this));
    layout->addWidget(m_maxFlashesEdit);

    // 确认按钮
    m_confirmButton = new QPushButton("Confirm", this);
    layout->addWidget(m_confirmButton);

   

    connect(m_confirmButton, &QPushButton::clicked, this, &SettingsWindow::onConfirmClicked);
}
int SettingsWindow::portAddress() const
{
    return m_portAddressEdit->text().toInt(nullptr, 16);
}
int SettingsWindow::flashInterval() const
{
    return m_flashIntervalEdit->text().toInt();
}

int SettingsWindow::flashDuration() const
{
    return m_flashDurationEdit->text().toInt();
}

int SettingsWindow::maxFlashes() const
{
    return m_maxFlashesEdit->text().toInt();
}

void SettingsWindow::onConfirmClicked()
{
    bool ok;
    short portAddress = m_portAddressEdit->text().toInt(&ok);
    qDebug()<<portAddress;
    emit settingsConfirmed(
        
        m_flashIntervalEdit->text().toInt(),
        m_flashDurationEdit->text().toInt(),
        m_maxFlashesEdit->text().toInt(),
        portAddress
        
    );
}
