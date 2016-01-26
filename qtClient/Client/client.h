#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QtWidgets>
#include <QVideoWidget>
#include <QtWebEngineWidgets>
#include <QUrl>

QT_BEGIN_NAMESPACE
//class QAction;
//class QMenu;
//class QTreeWidgetItem;
//class QWebEngineView;
//class QUrl;
QT_END_NAMESPACE

class Client : public QMainWindow
{
    //    The moc tool reads a C++ header file. If it finds one or more class declarations that contain the Q_OBJECT macro,
    //    it produces a C++ source file containing the meta-object code for those classes.
    //            Among other things, meta-object code is required for the signals and slots mechanism,
    //            the run-time type information, and the dynamic property system.
    Q_OBJECT


public:
    explicit Client(QWidget *parent = 0);
    ~Client();
protected:
    //Q_DECL_OVERRIDE:This macro can be used to declare an overriding virtual function.
    //Use of this markup will allow the compiler to generate an error if the overriding virtual function does not in fact override anything.
     void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void readSettings();
    void writeSettings();
    void videoMonitoring();
    void mapLocation();
    void accountSet();
    void logout();
    void addRoot(QString name,QString description);
    void addChild(QTreeWidgetItem *parent,QString name,QString description);
    QMenu *actionMenu;
    QMenu *helpMenu;
    QMenu *windowMenu;
    QToolBar *actionToolBar;
    QToolBar *navToolBar;
    QToolBar *accountToolBar;
    QAction *videoAct;
    QAction *mapAct;
    QAction *aboutAct;
    QAction *accountAct;
    QAction *logoutAct;
    QUrl url;
    QWebEngineView *webview;
    int progress;

private slots:
    void about();
};

#endif // CLIENT_H
