#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>
#include <QVBoxLayout>

#include "circlelayout.h"
#include "borderlayout.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void CircleLayoutSet();
    void SquareLayoutSet();
private:
    QTabWidget *m_tabWidget;
};
#endif // WIDGET_H
