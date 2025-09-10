#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QMainWindow>
#include "iplugin.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "../appcontext/appcontext.h"
#include "QDoubleSpinBox"
#include "QPushButton"
#include "qDebug"


class myplugin : public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IPlugin_iid) // 使用定义的IID
    Q_INTERFACES(IPlugin)

public:
    // 构造函数
    myplugin();
    // 传递值
    
    // 插件名称
    QString name() const override;
    // 创建窗口
    QWidget* createWidget(QWidget* parent = nullptr) override;


};

#endif // MYPLUGIN_H
