#include "myplugin.h"



myplugin::myplugin(){


}

QString myplugin::name() const { return "MyPlugin"; }

QWidget* myplugin::createWidget(QWidget* parent) {
    QWidget* widget = new QWidget(parent);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    // 创建spinbox并保存指针（使用局部变量+lambda捕获）
    QDoubleSpinBox* spinX = new QDoubleSpinBox(widget);
    QDoubleSpinBox* spinY = new QDoubleSpinBox(widget);
    QDoubleSpinBox* spinZ = new QDoubleSpinBox(widget);

    // 初始化spinbox属性（省略重复代码）
    spinX->setRange(0, 999999999);
    spinY->setRange(0, 999999999);
    spinZ->setRange(0, 999999999);
    spinX->setDecimals(0);
    spinY->setDecimals(0);
    spinZ->setDecimals(0);

    // 添加到布局（省略重复代码）
    layout->addWidget(new QLabel("X:", widget));
    layout->addWidget(spinX);
    layout->addWidget(new QLabel("Y:", widget));
    layout->addWidget(spinY);
    layout->addWidget(new QLabel("Z:", widget));
    layout->addWidget(spinZ);

    // 插件修改同步到主程序（已存在，保留）
    connect(spinX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
            [=](double value) {
        AppContext::instance().setValue("X", value);
    });
    connect(spinY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
            [=](double value) {
        AppContext::instance().setValue("Y", value);
    });
    connect(spinZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
            [=](double value) {
        AppContext::instance().setValue("Z", value);
    });

    // 新增：主程序修改同步到插件（监听AppContext变化）
    connect(&AppContext::instance(), &AppContext::dataChanged,
            widget, [=](const QString& key, const QVariant& value) {
        if (key == "X") {
            spinX->blockSignals(true);  // 避免信号循环
            spinX->setValue(value.toDouble());
            spinX->blockSignals(false);
        } else if (key == "Y") {
            spinY->blockSignals(true);
            spinY->setValue(value.toDouble());
            spinY->blockSignals(false);
        } else if (key == "Z") {
            spinZ->blockSignals(true);
            spinZ->setValue(value.toDouble());
            spinZ->blockSignals(false);
        }
    });
    // 插件createWidget函数中
    qDebug() << "插件AppContext地址:" << &AppContext::instance();
    return widget;
}