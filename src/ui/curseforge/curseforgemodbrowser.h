#ifndef CURSEFORGEMODBROWSER_H
#define CURSEFORGEMODBROWSER_H

#include "ui/explorebrowser.h"

#include "curseforge/curseforgeapi.h"

class CurseforgeMod;
class LocalModPath;
class CurseforgeModInfoWidget;
class CurseforgeFileListWidget;
class ExploreStatusBarWidget;
class QStatusBar;
class QStandardItemModel;
class LocalMod;
class QMenu;
namespace Ui {
class CurseforgeModBrowser;
}

class CurseforgeModBrowser : public ExploreBrowser
{
    Q_OBJECT

public:
    explicit CurseforgeModBrowser(QWidget *parent = nullptr, LocalMod *mod = nullptr, CurseforgeAPI::Section sectionId = CurseforgeAPI::Mod);
    ~CurseforgeModBrowser();

    void load() override;

    QWidget *infoWidget() const override;
    QWidget *fileListWidget() const override;
    CurseforgeMod *selectedMod() const;

    QList<QAction *> modActions() const override;
    QList<QAction *> pathActions() const override;

    ExploreBrowser *another() override;

signals:
    void selectedModsChanged(CurseforgeMod *selectedMod);

public slots:
    void refresh() override;
    void searchModByPathInfo(LocalModPath *path) override;
    void updateUi() override;

private slots:
    void getModList(QString name, int index = 0);
    void updateVersionList();
    void updateCategoryList(QList<CurseforgeCategoryInfo> list);
    void search();
    void updateStatusText();
    void on_loaderSelect_currentIndexChanged(int index);
    void on_sortSelect_currentIndexChanged(int);
    void on_actionMod_triggered();
    void on_actionWorld_triggered();
    void on_actionModpacks_triggered();
    void on_actionTexturepacks_triggered();
    void on_menuDownload_aboutToShow();
    void on_actionCopy_Website_Link_triggered();
    void on_actionOpen_Curseforge_Mod_Dialog_triggered();
    void on_actionOpen_Website_Link_triggered();

private:
    Ui::CurseforgeModBrowser *ui;
    CurseforgeAPI::Section sectionId_ = CurseforgeAPI::Mod;
    CurseforgeModInfoWidget *infoWidget_;
    CurseforgeFileListWidget *fileListWidget_;
    CurseforgeAPI *api_;
    QList<int> idList_;
    //open as a dialog to search mod
    LocalMod *localMod_;
    QString currentName_;
    int currentIndex_;
    int currentCategoryId_ = 0;
    GameVersion currentGameVersion_;
    ModLoaderType::Type currentLoaderType_ = ModLoaderType::Any;
    bool hasMore_ = false;
    bool isSearching_ = false;
    bool inited_ = false;
    CurseforgeMod* selectedMod_ = nullptr;
    std::unique_ptr<Reply<QList<CurseforgeModInfo> > > searchModsGetter_;
    std::unique_ptr<Reply<QList<CurseforgeCategoryInfo> > > sectionCategoriesGetter_;

    void loadMore() override;
    void onSelectedItemChanged(QStandardItem *item) override;
    QDialog *getDialog(QStandardItem *item) override;
    QWidget *getIndexWidget(QStandardItem *item) override;
    QMenu *getMenu() override;
};

#endif // CURSEFORGEMODBROWSER_H
