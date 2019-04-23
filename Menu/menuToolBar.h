#ifndef MENUTOOLBAR_H
#define MENUTOOLBAR_H

#include <QToolBar>
#include <Menu/menuButton.h>
class MenuToolBar : public QToolBar
{
    Q_OBJECT
public:
    MenuToolBar(QWidget *parent);
    void addBtn(MenuButton *btn);
    void init(void);
signals:
    void changeView(const QString &);
    void close();
public slots:
    void onButtonClick(const QString &action);
private:
    QAction *addWidget(QWidget *widget);
};

#endif // MENUTOOLBAR_H
