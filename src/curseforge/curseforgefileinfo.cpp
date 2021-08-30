#include "curseforgefileinfo.h"

#include <QDebug>

#include "util/tutil.hpp"

CurseforgeFileInfo CurseforgeFileInfo::fromVariant(const QVariant &variant)
{
    CurseforgeFileInfo fileInfo;

    fileInfo.id = value(variant, "id").toInt();
    fileInfo.displayName = value(variant, "displayName").toString();
    fileInfo.fileName = value(variant, "fileName").toString();
    fileInfo.downloadUrl = value(variant, "downloadUrl").toUrl();
    fileInfo.fileLength = value(variant, "fileLength").toInt();
    fileInfo.releaseType = value(variant, "releaseType").toInt();
    fileInfo.fileDate = value(variant, "fileDate").toDateTime();

    //I don't know why curseforge put game verison and modloader together
    auto versionList = value(variant, "gameVersion").toStringList();
    for(const auto &version : versionList){
        auto v = GameVersion::deduceFromString(version);
        if(v.has_value()){
            fileInfo.gameVersions << v.value();
            continue;
        }
        auto loaderType = ModLoaderType::fromString(version);
        if(loaderType != ModLoaderType::Any){
            fileInfo.modLoaders << loaderType;
            continue;
        }
    }

    return fileInfo;
}

int CurseforgeFileInfo::getId() const
{
    return id;
}

const QString &CurseforgeFileInfo::getDisplayName() const
{
    return displayName;
}

const QUrl &CurseforgeFileInfo::getDownloadUrl() const
{
    return downloadUrl;
}

const QList<GameVersion> &CurseforgeFileInfo::getGameVersions() const
{
    return gameVersions;
}

const QList<ModLoaderType::Type> &CurseforgeFileInfo::getModLoaders() const
{
    return modLoaders;
}

int CurseforgeFileInfo::getFileLength() const
{
    return fileLength;
}

const QString &CurseforgeFileInfo::getFileName() const
{
    return fileName;
}

int CurseforgeFileInfo::getReleaseType() const
{
    return releaseType;
}

const QDateTime &CurseforgeFileInfo::getFileDate() const
{
    return fileDate;
}
