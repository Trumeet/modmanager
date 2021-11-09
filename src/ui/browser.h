#ifndef BROWSER_H
#define BROWSER_H

#include <QWidget>

class Browser : public QWidget
{
    Q_OBJECT
public:
    explicit Browser(QWidget *parent = nullptr);
    virtual ~Browser() = 0;

    virtual QWidget *infoWidget() const;
};

#endif // BROWSER_H