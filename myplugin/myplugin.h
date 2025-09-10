#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QMainWindow>
#include "iplugin.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "appcontext.h"
#include "QDoubleSpinBox"


namespace Ui {
class myplugin;
}

class myplugin :  public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IPlugin_iid)
    Q_INTERFACES(IPlugin)


public:
    QString name() const override { return "MyPlugin"; }

    QWidget* createWidget(QWidget* parent = nullptr) override {
        // 弹窗
        QWidget* dialog = new QWidget(parent);
        dialog->setWindowTitle("XYZ 参数");
        dialog->setAttribute(Qt::WA_DeleteOnClose);

        // 布局
        QVBoxLayout* layout = new QVBoxLayout(dialog);

        // SpinBox 控件
        QDoubleSpinBox* spinX = new QDoubleSpinBox(dialog);
        QDoubleSpinBox* spinY = new QDoubleSpinBox(dialog);
        QDoubleSpinBox* spinZ = new QDoubleSpinBox(dialog);

        spinX->setRange(-10000, 10000);
        spinY->setRange(-10000, 10000);
        spinZ->setRange(-10000, 10000);

        spinX->setDecimals(3);
        spinY->setDecimals(3);
        spinZ->setDecimals(3);

        // 初始值从 AppContext 读取
        spinX->setValue(AppContext::instance().getValue("x").toDouble());
        spinY->setValue(AppContext::instance().getValue("y").toDouble());
        spinZ->setValue(AppContext::instance().getValue("z").toDouble());

        layout->addWidget(new QLabel("X 值:", dialog));
        layout->addWidget(spinX);
        layout->addWidget(new QLabel("Y 值:", dialog));
        layout->addWidget(spinY);
        layout->addWidget(new QLabel("Z 值:", dialog));
        layout->addWidget(spinZ);

        // 绑定 spinBox -> AppContext
        QObject::connect(spinX, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                         [](double v){ AppContext::instance().setValue("x", v); });
        QObject::connect(spinY, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                         [](double v){ AppContext::instance().setValue("y", v); });
        QObject::connect(spinZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                         [](double v){ AppContext::instance().setValue("z", v); });

        // 绑定 AppContext -> spinBox
        QObject::connect(&AppContext::instance(), &AppContext::dataChanged,
                         dialog, [=](const QString& key, const QVariant& value){
            if (key == "x") spinX->setValue(value.toDouble());
            if (key == "y") spinY->setValue(value.toDouble());
            if (key == "z") spinZ->setValue(value.toDouble());
        });

        dialog->setLayout(layout);
        dialog->resize(200, 200);

        return dialog;
    }

};



#endif // MYPLUGIN_H
