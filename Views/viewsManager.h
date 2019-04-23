#ifndef VIEWSMANAGER_H
#define VIEWSMANAGER_H

#include <QObject>
#include <Views/viewInterface.h>
#include <QMap>
class ViewsManager : public QObject
{
    Q_OBJECT
public:
    explicit ViewsManager(QObject *parent = 0);
    void init(void);
    QList<ViewInterface*> *produceWidgets(void);
signals:
    void ViewChanged(int);
public slots:
    void onViewChange(const QString &tab);
private:
    QMap<QString, ViewInterface*> m_viewsMap;
    QList<ViewInterface*> *m_widgetList;
};

#endif // VIEWSMANAGER_H
