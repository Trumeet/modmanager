#ifndef MODMANAGER_H
#define MODMANAGER_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "local/localmodpathinfo.h"
#include "browserselectorwidget.h"

class QListWidgetItem;
class LocalModPath;
class BrowserSelectorWidget;
class CurseforgeModBrowser;
class ModrinthModBrowser;
class OptifineModBrowser;
class ReplayModBrowser;

QT_BEGIN_NAMESPACE
namespace Ui { class ModManager; }
QT_END_NAMESPACE

class ModManager : public QMainWindow
{
    Q_OBJECT

public:
    ModManager(QWidget *parent = nullptr);
    ~ModManager();

    void resizeEvent(QResizeEvent *event);
private slots:
    void browserChanged(BrowserSelectorWidget::BrowserCategory category, int index);

    void syncPathList();
    void editLocalPath(int index);
    void on_actionPreferences_triggered();
    void on_actionManage_Browser_triggered();
    void customContextMenuRequested(const QPoint &pos);
    void on_action_About_Mod_Manager_triggered();
    void on_actionVisit_Curseforge_triggered();
    void on_actionVisit_Modrinth_triggered();
    void on_actionVisit_OptiFine_triggered();
    void on_actionVisit_ReplayMod_triggered();
private:
    Ui::ModManager *ui;
    BrowserSelectorWidget *browserSelector_;
    CurseforgeModBrowser *curseforgeModBrowser_;
    ModrinthModBrowser *modrinthModBrowser_;
    OptifineModBrowser *optifineModBrowser_;
    ReplayModBrowser *replayModBrowser_;

    QList<LocalModPath*> pathList_;
};
#endif // MODMANAGER_H
