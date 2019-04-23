#include "mainwnd.h"
#include "ui_mainwnd.h"
#include "commonLogger.h"
#include "Views/viewAddFormats.h"
#include "QStyleFactory"
#include "Menu/menuButton.h"
#include <QPushButton>
#include <QTreeWidget>
#include <QSettings>
#include <QDebug>
#include "version.h"
#include <QMessageBox>
#include <QToolBar>
#include <Menu/menuToolBar.h>
#include <undoStack.h>

MainWnd::MainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWnd)
{
    m_db_mng = DBManager::Manager();
    m_db_mng->init();
    m_stackedWidget = new QStackedWidget(this);
    ui->setupUi(this);
    m_viewMng = new ViewsManager();
    m_tEdit.setReadOnly(true);
    ui->dockLogger->setWidget(&m_tEdit);
    loggerTest();
    setDarkTheme();
    ui->mainToolBar->setIconSize(QSize(48,48));
    setMenu();
    readSettings();
    addWidgets();
    setCentralWidget(m_stackedWidget);
    setConnections();
    ui->menuToolBar->init();
}

MainWnd::~MainWnd()
{
    delete m_db_mng;
    delete ui;
}

void MainWnd::setMenu()
{
    for(int i=0; i < MenuButton::btnsCount; i++)
    {
        MenuButton *_btn = MenuButton::createButton(i, ui->menuToolBar);
        ui->menuToolBar->addBtn(_btn);
    }
}

void MainWnd::writeSettings()
{
    QSettings settings(author, designation);

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void MainWnd::readSettings()
{
    QSettings settings(author, designation);

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void MainWnd::setConnections()
{
    connect(m_viewMng, SIGNAL(ViewChanged(int)), m_stackedWidget, SLOT(setCurrentIndex(int)));
    connect(ui->menuToolBar, SIGNAL(changeView(QString)), m_viewMng, SLOT(onViewChange(QString)));
    connect(ui->menuToolBar, SIGNAL(close()), this, SLOT(close()));
}

void MainWnd::loggerTest()
{
    CommonLogger *logger = CommonLogger::Logger();
    logger->appendTEdit(&m_tEdit);
    logger->Info("Uruchomienie programu");
    logger->Warning("Uruchomienie programu");
    logger->Error("Uruchomienie programu");
}

void MainWnd::addWidgets()
{
    for(ViewInterface *el: *m_viewMng->produceWidgets())
        m_stackedWidget->addWidget(el);
}

void MainWnd::createActions()
{
    m_undoAction = UndoStack::Stack().createUndoAction(this, tr("&Undo"));
    m_undoAction->setShortcuts(QKeySequence::Undo);

    m_redoAction = UndoStack::Stack().createRedoAction(this, tr("&Redo"));
    m_redoAction->setShortcuts(QKeySequence::Redo);
    ui->menuEdit->addAction(m_undoAction);
    ui->menuEdit->addAction(m_redoAction);
}

void MainWnd::setMainWidget(ViewInterface *w)
{
    setCentralWidget(w);
    m_central = w;
}

void MainWnd::onBtnActTrig(QAction *)
{
    CommonLogger::Logger()->Error("what222");
}

void MainWnd::closeEvent(QCloseEvent *event)
{
    writeSettings();
    if(doClose())
        QMainWindow::closeEvent(event);
}

bool MainWnd::doClose()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Zamykanko"), tr("Zamknąć?"),
                                   QMessageBox::Yes|QMessageBox::No);
    return(reply == QMessageBox::Yes);
}

void MainWnd::setDarkTheme(void)
{
    qApp->setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);

    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}
