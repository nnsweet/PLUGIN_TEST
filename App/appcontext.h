#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>

class AppContext : public QObject {
    Q_OBJECT
public:
    static AppContext& instance() {
        static AppContext inst;
        return inst;
    }

    void setValue(const QString& key, const QVariant& value) {
        QMutexLocker locker(&m_mutex);
        m_data[key] = value;
        emit dataChanged(key, value);
    }

    QVariant getValue(const QString& key, const QVariant& def = {}) const {
        QMutexLocker locker(&m_mutex);
        return m_data.value(key, def);
    }

signals:
    void dataChanged(const QString& key, const QVariant& value);

private:
    AppContext() {}
    ~AppContext() {}
    Q_DISABLE_COPY(AppContext)

    mutable QMutex m_mutex;
    QMap<QString, QVariant> m_data;
};

#endif // APPCONTEXT_H
