#include "login.h"
#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Initializes the resources specified by the .qrc file with the specified base name. Normally,
//    when resources are built as part of the application, the resources are loaded automatically at startup.
//    The Q_INIT_RESOURCE() macro is necessary on some platforms for resources stored in a static library.
    Q_INIT_RESOURCE(res);
    a.setOrganizationName("PKU");
    a.setApplicationName("Remote 4G Monitoring System");
    Login login;
    Client client;
    //exec():Shows the dialog as a modal dialog, blocking until the user closes it.
    if(login.exec()==QDialog::Accepted)
    {
        client.show();
        return a.exec();
    }

    else
        return 0;
}
