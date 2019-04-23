#include "menuButton.h"
#include "commonLogger.h"
#include "QAbstractButton"
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QDebug>
#include <QSizePolicy>
#include <QEvent>
#include <QDynamicPropertyChangeEvent>
#include <QAction>

QList<QString> MenuButton::m_txts = QList<QString>()<<"Rozrys"<<"Reguły"<<"Meble"<<"Materiały"<<"Wyjście";

MenuButton::MenuButton(QString text, QWidget *parent):
    QToolButton(parent)
{
    setCheckable(true);
    setAutoExclusive(true);
    setText(text);
    m_txt = text;
    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    connect(this, SIGNAL(toggled(bool)), this, SLOT(onToggled(bool)));

}

void MenuButton::collapse()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setStartValue(this->geometry());
    QRect end = QRect(geometry().topLeft(), this->sizeHint()-QSize(20,0));
    animation->setEndValue(end);
    animation->setDuration(300);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
}

void MenuButton::expand()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setStartValue(this->geometry());
    QRect end = QRect(geometry().topLeft(), this->sizeHint());
    animation->setEndValue(end);
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
}

void MenuButton::onToggled(bool checked)
{
    if(checked)
    {
        collapse();
        emit clicked(m_txt);
    }
    else
    {
        expand();
    }
}

bool MenuButton::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::HoverEnter:
    case QEvent::MouseButtonPress:
    {
        collapse();
        break;
    }
    case QEvent::HoverLeave:
    {
        if(isChecked())
            break;
        expand();
        break;
    }

    default:
        break;
    }
    return QToolButton::event(e);
}

MenuButton *MenuButton::createButton(const int index, QWidget *parent)
{
    if(index>=btnsCount || index<0)
        Q_ASSERT(false);
    QString txt=m_txts[index];
    MenuButton *btn = new MenuButton(txt, parent);
    QString shortcut = "Ctrl+" + QString::number(index+1);
    btn->setShortcut(shortcut);
    return btn;
}

QSize MenuButton::sizeHint() const
{
    return QSize(120,30);
}
