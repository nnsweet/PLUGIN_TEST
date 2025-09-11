#include "myplugin.h"



myplugin::myplugin(){


}

QString myplugin::name() const { return "MyPlugin"; }

QWidget* myplugin::createWidget(QWidget* parent) {
    QWidget* widget = new QWidget(parent);
    // 布局
    QVBoxLayout* layout = new QVBoxLayout(widget);
    // 三个 spinbox
    QDoubleSpinBox* spinX = new QDoubleSpinBox(widget);
    spinX->setRange(0, 999999999);
    spinX->setDecimals(0);
    spinX->setValue(0.0);
    QDoubleSpinBox* spinY = new QDoubleSpinBox(widget);
    spinY->setRange(0, 999999999);
    spinY->setDecimals(0);
    spinY->setValue(0.0);
    QDoubleSpinBox* spinZ = new QDoubleSpinBox(widget);
    spinZ->setRange(0, 999999999);
    spinZ->setDecimals(0);
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
    // 实时同步X值到AppContext
    connect(spinX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        AppContext::instance().setValue("X", value);
    });
    // 实时同步Y值到AppContext
    connect(spinY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        AppContext::instance().setValue("Y", value);
    });
    // 实时同步Z值到AppContext
    connect(spinZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        AppContext::instance().setValue("Z", value);
    });

    //     // 关键2：优化主程序→插件的信号连接（上下文改为widget，避免控件销毁风险）
    // connect(&AppContext::instance(), &AppContext::dataChanged, widget, [spinX, spinY, spinZ](const QString& key, const QVariant& value) {
    //     if (key == "X") {
    //         spinX->setValue(value.toDouble());
    //         qDebug() << "插件接收X值：" << value.toDouble();
    //     } else if (key == "Y") {
    //         spinY->setValue(value.toDouble());
    //         qDebug() << "插件接收Y值：" << value.toDouble();
    //     } else if (key == "Z") {
    //         spinZ->setValue(value.toDouble());
    //         qDebug() << "插件接收Z值：" << value.toDouble();
    //     }
    // });

    // 关键添加：主动获取主程序已有的值，初始化插件spinBox
    double initX = AppContext::instance().getValue("X").toDouble();
    double initY = AppContext::instance().getValue("Y").toDouble();
    double initZ = AppContext::instance().getValue("Z").toDouble();
    spinX->setValue(initX);
    spinY->setValue(initY);
    spinZ->setValue(initZ);
    qDebug() << "插件初始化值：X=" << initX << ", Y=" << initY << ", Z=" << initZ;



    return widget;
}
