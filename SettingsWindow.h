// SettingsWindow.h
#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QIntValidator>


class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    SettingsWindow(QWidget* parent = nullptr);

    // 获取输入的参数
    int flashInterval() const;
    int flashDuration() const;
    int maxFlashes() const;
    int portAddress() const;  // 端口地址


signals:
    void settingsConfirmed(int flashInterval, int flashDuration, int maxFlashes,short portAddre);


private slots:
    void onConfirmClicked();

private:
    QLineEdit* m_flashIntervalEdit;
    QLineEdit* m_flashDurationEdit;
    QLineEdit* m_maxFlashesEdit;
    QLineEdit* m_portAddressEdit;
    QPushButton* m_confirmButton;
    //参数传递
    QLineEdit* m_startDataEdit;
    QLineEdit* m_endDataEdit;
};
