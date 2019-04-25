#include "dbManager.h"
#include <QMessageBox>
#include "version.h"
#include <commonLogger.h>
#include <QSqlQuery>
DBManager *DBManager::m_instance = nullptr;
DBManager::DBManager(QObject *parent) : QObject(parent)
{
    m_tables_names << "materials" << "furnitures";

}

DBManager *DBManager::Manager()
{
    if(!m_instance)
        m_instance = new DBManager();
    return m_instance;
}

DBManager::~DBManager()
{
    m_db->close();
}

QSqlDatabase *DBManager::Connection()
{
    return Manager()->m_db;
}

QSqlError DBManager::init()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        CommonLogger::Logger()->Error(tr("Nie można załadować sterownika SQLITE. Dalsza praca niemożliwa."));
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    m_db->setDatabaseName(db_name);
    if (!m_db->open())
    {
        CommonLogger::Logger()->Error(m_db->lastError().text());
        return m_db->lastError();
    }
    QStringList tables = m_db->tables();
    for(auto &table: m_tables_names)
    {
        if(!tables.contains(table, Qt::CaseInsensitive))
        {
            QSqlError e = create_table(table);
            if(e.isValid())
            {
                CommonLogger::Logger()->Error(e.text());
                return e;
            }
        }
    }
    return QSqlError();
}

QSqlError DBManager::create_table(const QString &tab_name)
{
    QSqlQuery q;
    if(tab_name == "materials")
    {
        if (!q.exec(QLatin1String("create table materials(name varchar primary key, dir varchar, prise integer, width integer, height integer, thickness integer)")))
        {
            CommonLogger::Logger()->Debug(q.lastError().text());
            return q.lastError();
        }
        if (!q.prepare(QLatin1String("insert into materials(name, dir, prise, width, height, thickness) values(?, ?, ?, ?, ?, ?)")))
            return q.lastError();
        QStringList _str_list;
        _str_list << "jesion" << "../images/jesion.jpg" << "222" << "1800" << "2800" << "18";
        addBindValues(q,_str_list);
        _str_list.clear();
        _str_list << "jesion2" << "../images/jesion2.jpg" << "223" << "1801" << "2801" << "19";
        addBindValues(q,_str_list);
    }
    else if(tab_name == "furnitures")
    {
        if(!q.exec(QLatin1String("create table furnitures(name varchar primary key, dir varchar, prise integer, width integer, height integer, thickness integer)")))
        {
            CommonLogger::Logger()->Debug(q.lastError().text());
            return q.lastError();
        }
    }
    else if(tab_name == "furnitures_elements")
    {
        if(!q.exec(QLatin1String("create table furnitures_elements(id int autoincrement primary key, furniture_key varchar, el_width_dependence integer, width integer, height integer, thickness integer)")))
        {
            CommonLogger::Logger()->Debug(q.lastError().text());
            return q.lastError();
        }
    }
    else
    {
        CommonLogger::Logger()->Debug("Nieobsługiwana tabela");
    }
    return QSqlError();
}

void DBManager::addBindValues(QSqlQuery &q, const QStringList &str_list)
{
    for(auto &el: str_list)
    {
        q.addBindValue(el);
    }
    q.exec();
}
