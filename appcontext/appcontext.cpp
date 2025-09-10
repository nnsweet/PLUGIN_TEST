#include "appcontext.h"
#include <QMap>
#include <QMutexLocker>

// 单例实例化
AppContext& AppContext::instance() {
    static AppContext inst;
    return inst;
}

// 设置值并触发信号
void AppContext::setValue(const QString& key, const QVariant& value) {
    QMutexLocker locker(&m_mutex);
    m_data[key] = value;
    emit dataChanged(key, value);
}

// 获取值
QVariant AppContext::getValue(const QString& key, const QVariant& def) const {
    QMutexLocker locker(&m_mutex);
    return m_data.value(key, def);
}
