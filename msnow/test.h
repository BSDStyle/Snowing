#ifndef TEST_H
#define TEST_H

#include "about.h"

#include <QMainWindow>
#include <QLabel>
#include <QPoint>
#include <QLabel>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QMatrix>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QList>

#include <QCloseEvent>
#define MAX_SNOW_IMG 33

namespace Ui {
class test;
}

typedef struct{
    int     m_speed;
    QString m_path;
    QPoint  m_qp;
    QLabel  m_label;
    QPixmap m_pixmap;
    QMatrix m_matrix;
}snow;

class test : public QMainWindow
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0);
    void setAttr(QList<QLabel> &label, QList<QPixmap> &pixmap);
    ~test();
protected:
    void timerEvent(QTimerEvent *event);

    void getScreenInfo();

    void setSnowNextPistion(snow &s);

    void closeEvent(QCloseEvent *e);

public slots:
    void showsnow();
    void showRMouse(QSystemTrayIcon::ActivationReason event);


    void snowexit();
    void snowtop();

    void showabout();


private:
    Ui::test *ui;
    QLabel *ql;

    QPoint  m_qp;
    QMatrix m_mx;
    snow m_snow[MAX_SNOW_IMG];

    QSystemTrayIcon* m_SystrayIcon;

//    QList<snow>  m_slist;
    QMenu *m_menu[2];
    QAction *m_action[3];

    QIcon *exit_icon;

    about *ab;

    int m_id;
    int m_tr;
    int x;
    int y;

    int m_sW;
    int m_sH;

};

#endif // TEST_H
