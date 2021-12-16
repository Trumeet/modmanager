#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>

class Browser : public QMainWindow
{
    Q_OBJECT
public:
    explicit Browser(QWidget *parent = nullptr);
    virtual ~Browser() = 0;

    void show();

    virtual void load();

    virtual QWidget *infoWidget() const;
    virtual QWidget *fileListWidget() const;
    virtual QList<QAction *> modActions() const;
    virtual QList<QAction *> pathActions() const;
    virtual void onModMenuAboutToShow();
    virtual void onModMenuAboutToHide();
    virtual QIcon icon() const = 0;
    virtual QString name() const = 0;
};

#endif // BROWSER_H
