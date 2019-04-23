#ifndef MAINWND_H
#define MAINWND_H

#include <QMainWindow>
#include <QTextEdit>
#include <Views/viewInterface.h>
#include <Views/viewsManager.h>
#include <QWidget>
#include <dbManager.h>
#include <QStackedWidget>
namespace Ui {
class MainWnd;
}

class MainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWnd(QWidget *parent = 0);
    ~MainWnd();

private:
    void setDarkTheme(void);
    void closeEvent(void);
    void setMenu(void);
    void writeSettings(void);
    void readSettings(void);
    void setConnections(void);
    void loggerTest(void);
    void addWidgets(void);
    void createActions(void);
    Ui::MainWnd *ui;
    QTextEdit m_tEdit;
    ViewInterface *m_central;
    ViewsManager *m_viewMng;
    DBManager *m_db_mng;
    QStackedWidget *m_stackedWidget;
    QAction *m_undoAction;
    QAction *m_redoAction;

private slots:
    void setMainWidget(ViewInterface*);
    void onBtnActTrig(QAction*);
protected:
    void closeEvent(QCloseEvent *event) override;
    bool doClose(void);
};

#endif // MAINWND_H
