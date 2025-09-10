#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtPlugin>
#include <QWidget>

// 插件接口
class IPlugin {
public:
    virtual ~IPlugin() {}
    virtual QString name() const = 0;
    virtual QWidget* createWidget(QWidget* parent = nullptr) = 0;
};

#define IPlugin_iid "org.demo.Plugin.IPlugin"
Q_DECLARE_INTERFACE(IPlugin, IPlugin_iid)

#endif // IPLUGIN_H
