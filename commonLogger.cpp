#include "commonLogger.h"
#include <QDebug>
#include <QDateTime>
CommonLogger* CommonLogger::m_instance = nullptr;
CommonLogger::CommonLogger()
{
}

CommonLogger* CommonLogger::Logger()
{
    if(m_instance == nullptr)
    {
        m_instance = new CommonLogger();
    }
    return m_instance;
}
void CommonLogger::appendTEdit(QTextEdit* tEdit)
{
    this->m_tEdits.append(tEdit);
}

void CommonLogger::Debug(const QString& msg)
{
    QString message = "<font color=\"Green\">DEBUG::" + QDateTime::currentDateTime().time().toString() + " - " + msg + "</font><br>";
    report(message);
}

void CommonLogger::report(const QString &message)
{
    foreach (QTextEdit *tEdit, this->m_tEdits)
    {
        tEdit->insertHtml(message);
    }
    qDebug() << message;
}

void CommonLogger::Info(const QString& msg)
{
    QString message = "<font color=\"White\">INFO::" + QDateTime::currentDateTime().time().toString() + " - " + msg + "</font><br>";
    report(message);
}

void CommonLogger::Warning(const QString& msg)
{
    QString message = "<font color=\"Orange\">Warning::" + QDateTime::currentDateTime().time().toString() + " - " + msg + "</font><br>";
    this->report(message);
}

void CommonLogger::Error(const QString& msg)
{
    QString message = "<font color=\"Red\">Error::" + QDateTime::currentDateTime().time().toString() + " - " + msg + "</font><br>";
    this->report(message);
}
