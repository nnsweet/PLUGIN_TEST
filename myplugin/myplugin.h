#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QMainWindow>
#include "iplugin.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "appcontext.h"
#include "QDoubleSpinBox"
#include "QPushButton"
#include "qDebug"


class myplugin : public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IPlugin_iid) // 使用定义的IID
    Q_INTERFACES(IPlugin)

public:
    QString name() const override { return "MyPlugin"; }

    QWidget* createWidget(QWidget* parent = nullptr) override {
        QWidget* widget = new QWidget(parent);

        // 布局
        QVBoxLayout* layout = new QVBoxLayout(widget);

        // 三个 spinbox
        QDoubleSpinBox* spinX = new QDoubleSpinBox(widget);
        spinX->setRange(-1000, 1000);
        spinX->setDecimals(3);
        spinX->setValue(0.0);

        QDoubleSpinBox* spinY = new QDoubleSpinBox(widget);
        spinY->setRange(-1000, 1000);
        spinY->setDecimals(3);
        spinY->setValue(0.0);

        QDoubleSpinBox* spinZ = new QDoubleSpinBox(widget);
        spinZ->setRange(-1000, 1000);
        spinZ->setDecimals(3);
        spinZ->setValue(0.0);

        layout->addWidget(new QLabel("X:", widget));
        layout->addWidget(spinX);
        layout->addWidget(new QLabel("Y:", widget));
        layout->addWidget(spinY);
        layout->addWidget(new QLabel("Z:", widget));
        layout->addWidget(spinZ);

        QPushButton* okBtn = new QPushButton("确定", widget);
        layout->addWidget(okBtn);

        widget->setLayout(layout);

        // 点击确定时打印当前值
        QObject::connect(okBtn, &QPushButton::clicked, widget, [=]() {
            qDebug() << "X=" << spinX->value()
                     << "Y=" << spinY->value()
                     << "Z=" << spinZ->value();
            widget->close(); // 关闭窗口
        });

        return widget;
    }
};

#endif // MYPLUGIN_H
