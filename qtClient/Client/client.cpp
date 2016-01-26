#include "client.h"



/*
 * 当一个QObject对象在堆上创建的时候，Qt 会同时为其创建一个对象树。
 * Qt 保证的是，任何对象树中的 QObject对象 delete 的时候， 如果这个对象有 parent，则自动将其从 parent 的children()列表中删除；
 * 如果有孩子，则自动 delete 每一个孩子。 Qt 保证没有QObject会被 delete 两次，这是由析构顺序决定的。
 * 局部对象的析构顺序应该按照其创建顺序的相反过程。
 * 在 Qt 中，尽量在构造的时候就指定 parent 对象，并且大胆在堆上创建。
*/

Client::Client(QWidget *parent) :
    QMainWindow(parent)

{
    this->setWindowTitle(tr("Remote 4G Monitoring System"));
    url = QUrl("http://www.baidu.com");
    webview = new QWebEngineView(this);
    webview->load(url);
    setCentralWidget(webview);
    this->createActions();
    this->createMenus();
    this->createToolBars();
    this->createStatusBar();
    this->readSettings();
    this->createDockWindows();
//    QVideoWidget *videoWidget = new QVideoWidget;
//    this->setCentralWidget(videoWidget);




}

Client::~Client()
{

}

void Client::closeEvent(QCloseEvent *event)
{
    //save the user's preferences to disk and accept the close event;
    writeSettings();
    event->accept();

}

void Client::createActions()
{
    //为文件取别名
    // a QAction emits a triggered() signal whenever the user invokes the action
    videoAct = new QAction(QIcon(":/imgs/video"), tr("&Video Monitoring"), this);
    videoAct->setShortcut(QKeySequence(tr("Ctrl+V")));
    videoAct->setStatusTip(tr("Start Video Monitoring"));
    connect(videoAct, &QAction::triggered, this, &Client::videoMonitoring);

    mapAct = new QAction(QIcon(":/imgs/map"), tr("&Map Location"), this);
    mapAct->setShortcut(QKeySequence(tr("Ctrl+M")));
    mapAct->setStatusTip(tr("Start Map Location"));
    connect(mapAct, &QAction::triggered, this, &Client::mapLocation);


    aboutAct=new QAction( tr("&About"),this);
    aboutAct->setStatusTip(tr("About the Application"));
    connect(aboutAct, &QAction::triggered, this, &Client::about);


    accountAct = new QAction(QIcon(":/imgs/account"), tr("&Account Setting"), this);
    accountAct->setShortcut(QKeySequence(tr("Ctrl+A")));
    accountAct->setStatusTip(tr("Account Setting"));
    connect(accountAct, &QAction::triggered, this, &Client::accountSet);

    logoutAct = new QAction(QIcon(":/imgs/logout"), tr("&Logout"), this);
    logoutAct->setShortcut(QKeySequence(tr("Ctrl+O")));
    logoutAct->setStatusTip(tr("Logout"));
    connect(logoutAct, &QAction::triggered, this, &Client::logout);

}

void Client::createMenus()
{
    //menuBar()是QMainWindow提供的函数
        actionMenu = menuBar()->addMenu(tr("&Action"));
        actionMenu->addAction(videoAct);
        actionMenu->addAction(mapAct);

        windowMenu=menuBar()->addMenu(tr("&Window"));

        helpMenu = menuBar()->addMenu(tr("&Help"));
        helpMenu->addAction(aboutAct);



}

void Client::createToolBars()
{
    //一个窗口只有一个菜单栏，但是却可能有多个工具栏

        actionToolBar = addToolBar(tr("&Action"));
        actionToolBar->addAction(videoAct);
        actionToolBar->addAction(mapAct);

        navToolBar = addToolBar(tr("Navigation"));
        navToolBar->addAction(webview->pageAction(QWebEnginePage::Back));
        navToolBar->addAction(webview->pageAction(QWebEnginePage::Forward));
        navToolBar->addAction(webview->pageAction(QWebEnginePage::Reload));
        navToolBar->addAction(webview->pageAction(QWebEnginePage::Stop));

        accountToolBar = addToolBar(tr("&Account"));
        QWidget* spacer = new QWidget();
        spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        accountToolBar->addWidget(spacer);;
        accountToolBar->addAction(accountAct);
        accountToolBar->addAction(logoutAct);
}

void Client::createStatusBar()
{
    //Like with QMainWindow::menuBar(), the widget is automatically created the first time the function is called.
    statusBar()->showMessage(tr("Ready"));
}

void Client::createDockWindows()
{

     QDockWidget *equidock = new QDockWidget(tr("Equipments"), this);
     QTreeWidget *treeWidget = new QTreeWidget(equidock);
     treeWidget->setColumnCount(1);
     treeWidget->setHeaderLabel(tr("Name"));
     treeWidget->setSortingEnabled(true);
     QList<QTreeWidgetItem *> items;
        for (int i = 0; i < 10; ++i)
            items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Equipment: %1").arg(i))));
     treeWidget->insertTopLevelItems(0, items);

     equidock->setWidget(treeWidget);
     addDockWidget(Qt::RightDockWidgetArea, equidock);
     windowMenu->addAction(equidock->toggleViewAction());


     QDockWidget *userdock = new QDockWidget(tr("App Users"), this);
     userdock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
     QTreeWidget *appUserWidget = new QTreeWidget(userdock);
     appUserWidget->setColumnCount(2);
     appUserWidget->setHeaderLabel(tr("Name"));
     QStringList labels;
        labels << "Name" << "Location";
     appUserWidget->setHeaderLabels(labels);
    //appUserWidget->setHeaderHidden(true);
     appUserWidget->setSortingEnabled(true);
     QList<QTreeWidgetItem *> appitems;
        for (int i = 0; i < 10; ++i)
            appitems.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("User: %1").arg(i))));
     appUserWidget->insertTopLevelItems(0, appitems);





     userdock->setWidget(appUserWidget);
     addDockWidget(Qt::RightDockWidgetArea, userdock);
     windowMenu->addAction(userdock->toggleViewAction());


//    connect(equipmentList, SIGNAL(currentTextChanged(QString)),
//            this, SLOT(insertCustomer(QString)));
//    connect(paragraphsList, SIGNAL(currentTextChanged(QString)),
//            this, SLOT(addParagraph(QString)));
}

void Client::readSettings()
{
//    The QSettings class provides a high-level interface for storing settings permanently on disk.
//            On Windows, it uses the (in)famous Windows registry;
    QSettings settings("PKU", "Remote 4G Monitoring System");
// We use QSettings::value() to extract the value of the "pos" and "size" settings.
// The second argument to QSettings::value() is optional and specifies a default value for the setting if there exists none.
// This value is used the first time the application is run.
   // QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(800, 600)).toSize();
    resize(size);
   // move(pos);
}

void Client::writeSettings()
{
    QSettings settings("PKU", "Remote 4G Monitoring System");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void Client::videoMonitoring()
{
    QMessageBox::information(this, tr("Information"), tr("Video Monitoring"));
}
void Client::mapLocation()
{
    QMessageBox::information(this, tr("Information"), tr("Map Location"));
}

void Client::accountSet()
{
    //打开网页用户账号设置页面
}

void Client::logout()
{

}

void Client::addRoot(QString name, QString description)
{

}

void Client::addChild(QTreeWidgetItem *parent, QString name, QString description)
{

}

void Client::about()
{
    QMessageBox::about(this, tr("About Application"),
               tr("The Application<b> 4G Remote Monitoring System</b> is developed by Peking University"
                  ", provide functions like video monitoring,"
                  "map location, and sensor monitoring.<br>For more information,contact dingruoting0103@gmail.com"));
}
