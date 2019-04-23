#ifndef COMMONLOGGER_H
#define COMMONLOGGER_H

#include <QTextEdit>
#include <QList>
class CommonLogger
{
public:
    static CommonLogger* Logger();
    void Debug(const QString&);
    void Info(const QString&);
    void Warning(const QString&);
    void Error(const QString&);
    void appendTEdit(QTextEdit*);

private:
    CommonLogger();
    static CommonLogger *m_instance;
    void report(const QString&);
    QList<QTextEdit*> m_tEdits;
};

#endif // COMMONLOGGER_H
