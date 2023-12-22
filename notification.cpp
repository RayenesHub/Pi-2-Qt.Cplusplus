#include "notification.h"
#include "aliment.h"

void notification::notification_nouv()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("bell.svg"));
    //notifyIcon->setVisible(1);
        notifyIcon->show();
        notifyIcon->showMessage("Heartshare", "Un nouveau aliment est ajouté !", QSystemTrayIcon::Information, 15000);

}
void notification::notification_outofstock()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("bell.svg"));
    notifyIcon->setVisible(1);
        notifyIcon->show();
        notifyIcon->showMessage("Heartshare", "un aliment est supprimer du stock !", QSystemTrayIcon::Information, 15000);

}
