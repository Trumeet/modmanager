#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QTextCodec>
#include <QStandardPaths>
#include <QDebug>

#define getterAndSetter(name, type, key, defaultValue) \
    void set##name(const decltype(QVariant().to##type()) &key){\
        setValue(#key, key);\
    }\
    \
    decltype(QVariant().to##type()) get##name() const{\
        return value(#key, old_.value(#key, defaultValue)).to##type();/*for compatibility*/\
    }

#define getterAndSetter_prefix(name, type, key, prefix, defaultValue) \
    void set##name(const decltype(QVariant().to##type()) &key){\
        setValue(QString(prefix) + "/" + #key, key);\
    }\
    \
    decltype(QVariant().to##type()) get##name() const{\
        return value(QString(prefix) + "/" + #key, defaultValue).to##type();\
    }

class Config : private QSettings
{
public:
    explicit Config() :
        QSettings(),
        old_("modmanager.ini", QSettings::IniFormat)
    {
        setIniCodec(QTextCodec::codecForName("UTF-8"));
        old_.setIniCodec(QTextCodec::codecForName("UTF-8"));
    }

    //General
    getterAndSetter(DownloadPath, String, downloadPath, QStandardPaths::writableLocation(QStandardPaths::DownloadLocation))
    getterAndSetter(SearchResultCount, Int, searchResultCount, 30)
    enum OptifineSourceType{ Official, BMCLAPI };
    getterAndSetter(OptifineSource, Int, optifineSource, Official)
    getterAndSetter(ShowModrinthSnapshot, Bool, showModrinthSnapshot, false)

    //Local
    getterAndSetter(CommonPath, String, commonPath, "")
    enum RightClickTagMenuType{ AllAvailable, CurrentPath };
    getterAndSetter(RightClickTagMenu, Int, rightClickTagMenu, AllAvailable)
    getterAndSetter(StarredAtTop, Bool, starredAtTop, true)
    getterAndSetter(DisabedAtBottom, Bool, disabedAtBottom, true)
    enum VersionMatchType{ MinorVersion, MajorVersion };
    getterAndSetter(VersionMatch, Int, versionMatch, MinorVersion);
    enum LoaderMatchType{ ExactMatch, IncludeUnmarked };
    getterAndSetter(LoaderMatch, Int, loaderMatch, IncludeUnmarked);
    getterAndSetter(UseCurseforgeUpdate, Bool, useCurseforgeUpdate, true)
    getterAndSetter(UseModrinthUpdate, Bool, useModrinthUpdate, true)
    enum PostUpdateType{ Delete, Keep, DoNothing };
    getterAndSetter(PostUpdate, Int, postUpdate, Keep)
    enum UpdateCheckIntervalType{ Always, EveryDay, Never };
    getterAndSetter(UpdateCheckInterval, Int, updateCheckIntervalType, EveryDay)

    //Network
    getterAndSetter(ThreadCount, Int, threadCount, 8)
    getterAndSetter(DownloadCount, Int, downloadCount, 16)

    //Path List
    getterAndSetter(LocalPathList, List, localPathList, QVariant())
    //Download List
    getterAndSetter(DownloaderList, List, downloaderList, QVariant())

    //others
    getterAndSetter(TabSelectBarArea, Int, tabSelectBarArea, Qt::LeftToolBarArea)
    getterAndSetter(MainWindowWidth, Int, mainWindowWidth, 1440);
    getterAndSetter(MainWindowHeight, Int, mainWindowHeight, 900);
private:
    QSettings old_;
};

#endif // CONFIG_H