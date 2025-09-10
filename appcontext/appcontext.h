#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QObject>
#include <QVariant>
#include <QMutex>

// 共享库导出宏
#ifdef SHAREDCONTEXT_LIBRARY
#define SHAREDCONTEXT_EXPORT Q_DECL_EXPORT
#else
#define SHAREDCONTEXT_EXPORT Q_DECL_IMPORT
#endif

class SHAREDCONTEXT_EXPORT AppContext : public QObject {
    Q_OBJECT
public:
    static AppContext& instance();

    void setValue(const QString& key, const QVariant& value);
    QVariant getValue(const QString& key, const QVariant& def = {}) const;

signals:
    void dataChanged(const QString& key, const QVariant& value);

private:
    AppContext() = default;
    ~AppContext() = default;
    Q_DISABLE_COPY(AppContext)

    mutable QMutex m_mutex;
    QMap<QString, QVariant> m_data; // 声明为类成员，定义移至cpp
};

#endif // APPCONTEXT_H
