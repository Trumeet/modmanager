#ifndef LOCALMODBROWSER_H
#define LOCALMODBROWSER_H

#include "ui/browser.h"
#include "local/localmodpathinfo.h"

#include <QButtonGroup>
#include <QModelIndex>

class QListWidgetItem;
class QStandardItemModel;
class LocalMod;
class QStandardItem;
class QMenu;
class LocalModPath;
class LocalModFilter;
class QStatusBar;
class QProgressBar;
class LocalModInfoWidget;
class LocalFileListWidget;
namespace Ui {
class LocalModBrowser;
}
class LocalModBrowser : public Browser
{
    Q_OBJECT
public:
    enum { ModColumn, NameColumn, IdColumn, VersionColumn, EnableColumn, StarColumn, TagsColumn, FileDateColumn, FileSizeColumn, FileNameColumn, CurseforgeIdColumn, CurseforgeFileIdColumn, ModrinthIdColumn, ModrinthFileIdColumn, DescriptionColumn };
    explicit LocalModBrowser(QWidget *parent, LocalModPath *modPath);
    ~LocalModBrowser();

    bool isLoading() const;
    LocalModPath *modPath() const;
    QWidget *infoWidget() const override;
    QWidget *fileListWidget() const override;
signals:
    void loadFinished();

    void findNewOnCurseforge(LocalModPathInfo info);
    void findNewOnModrinth(LocalModPathInfo info);
    void findNewOnOptifine(LocalModPathInfo info);
    void findNewOnReplay(LocalModPathInfo info);
public slots:
    void reload();
    void updateModList();
    void updateUi();

private slots:
    void onLoadStarted();
    void onLoadProgress(int loadedCount, int totalCount);
    void onLoadFinished();

    void onCheckWebsitesStarted();
    void onWebsiteCheckedCountUpdated(int checkedCount);
    void onWebsitesReady();

    void onCheckUpdatesStarted();
    void onCheckCancelled();
    void onUpdateCheckedCountUpdated(int updateCount, int checkedCount, int totalCount);
    void onUpdatesReady(int failedCount = 0);
    void onUpdatableCountChanged();

    void onUpdatesStarted();
    void onUpdatesProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onUpdatesDoneCountUpdated(int doneCount, int totalCount);
    void onUpdatesDone(int successCount, int failCount);

    void filterList();
    void updateStatusText();
    void updateProgressBar();
    QMenu *onCustomContextMenuRequested(const QModelIndex &index);
    void updateIndexWidget();

    void on_checkUpdatesButton_clicked();
    void on_openFolderButton_clicked();
    void on_updateAllButton_clicked();
    void on_hideUpdatesButton_clicked();
    void onItemSelected(const QModelIndex &index);
    void onItemDoubleClicked(const QModelIndex &index);
    void on_modListView_customContextMenuRequested(const QPoint &pos);
    void on_modIconListView_customContextMenuRequested(const QPoint &pos);
    void on_modTreeView_customContextMenuRequested(const QPoint &pos);
    void onModTreeViewHeaderCustomContextMenuRequested(const QPoint &pos);
    void updateSections();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::LocalModBrowser *ui;
    QStandardItemModel *model_;
    LocalModInfoWidget *infoWidget_;
    LocalFileListWidget *fileListWidget_;
    QStatusBar *statusBar_;
    QProgressBar *progressBar_;
    QButtonGroup *viewSwitcher_;
    LocalModPath *modPath_;
    LocalModFilter *filter_;
    int hiddenCount_ = 0;
    bool isChecking_ = false;
    bool isUpdating_ = false;
};

#endif // LOCALMODBROWSER_H
