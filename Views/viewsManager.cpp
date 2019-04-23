#include "viewsManager.h"
#include "Views/viewAddFormats.h"
#include "Views/viewMaterials.h"
#include "Views/viewFurnitures.h"
#include <commonLogger.h>
ViewsManager::ViewsManager(QObject *parent) : QObject(parent)
{
    m_widgetList = new QList<ViewInterface*>();
    ViewInterface *el = new ViewMaterials();
    m_widgetList->append(el);
    m_viewsMap[tr("Materiały")] = el;
    ViewInterface *el1 = new ViewAddFormats();
    m_widgetList->append(el1);
    m_viewsMap[tr("Rozrys")] = el1;
    ViewInterface *el2 = new ViewFurnitures();
    m_widgetList->append(el2);
    m_viewsMap[tr("Meble")] = el2;
}

void ViewsManager::init()
{
    emit ViewChanged(1);
}

QList<ViewInterface *> *ViewsManager::produceWidgets()
{
    return m_widgetList;
}

void ViewsManager::onViewChange(const QString &tab)
{
    ViewInterface *_view = m_viewsMap.value(tab);
    int _pos = m_widgetList->indexOf(_view);
    if(_pos != -1)
        emit ViewChanged(_pos);
}
