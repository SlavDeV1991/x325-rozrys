#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
class DBManager : public QObject
{
    Q_OBJECT
public:
    static DBManager *Manager();
    ~DBManager();
    static QSqlDatabase *Connection(void);
    QSqlError init(void);
private:
    static DBManager *m_instance;
    QString m_path;
    QSqlDatabase *m_db;
    QStringList m_tables_names;
    QSqlError create_table(const QString &tab_name);
    void addBindValues(QSqlQuery &q, const QStringList &str_list);
    explicit DBManager(QObject *parent = 0);
signals:

public slots:
};

#endif // DBMANAGER_H
