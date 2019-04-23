#include "menuToolBar.h"
#include <commonLogger.h>

MenuToolBar::MenuToolBar(QWidget *parent = Q_NULLPTR):
    QToolBar(parent)
{
    CommonLogger::Logger()->Error("what");
}

void MenuToolBar::addBtn(MenuButton *btn)
{
    addWidget(btn);
    connect(btn, SIGNAL(clicked(QString)), this, SLOT(onButtonClick(QString)));
}

void MenuToolBar::init()
{

}

void MenuToolBar::onButtonClick(const QString &action)
{
    CommonLogger::Logger()->Error("btn click");
    CommonLogger::Logger()->Error(action);
    if(action != tr("Wyjście"))
        emit changeView(action);
    else
    {
        CommonLogger::Logger()->Error("close");
        emit close();
    }
}

QAction *MenuToolBar::addWidget(QWidget *widget)
{
    return QToolBar::addWidget(widget);
}
