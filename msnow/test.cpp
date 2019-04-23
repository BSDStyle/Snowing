#include "test.h"
#include "ui_test.h"

#include <QLabel>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QWidget>
#include <QTransform>
#include <QDebug>
#include <QDesktopWidget>
#include <windows.h>
#include <QListIterator>
#include <QIcon>
#include <time.h>

test::test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);

    m_menu[0] = new QMenu(this);

    m_action[0] = new QAction(m_menu[0]);
    m_action[1] = new QAction(m_menu[0]);
    m_action[2] = new QAction(m_menu[0]);

    m_action[0]->setText("退出");
    m_action[1]->setText("雪花在屏幕最前");
    m_action[2]->setText("关于");

    m_menu[0]->addAction(m_action[0]);
    m_menu[0]->addAction(m_action[1]);
    m_menu[0]->addAction(m_action[2]);

    this->ab = new about;

    this->m_SystrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon("./snow.ico");
    m_SystrayIcon->setIcon(icon);
    m_SystrayIcon->setToolTip(QObject::trUtf8("桌面下雪啦"));
    m_SystrayIcon->setContextMenu(m_menu[0]);
    m_SystrayIcon->show();

    exit_icon = new QIcon("./snow.ico");

//   setAttribute(Qt::WA_TranslucentBackground, true);
   setWindowFlags(Qt::FramelessWindowHint        //去边框
                                    |Qt::X11BypassWindowManagerHint     //linux下脱离任务管理器
                                    |Qt::WindowStaysOnBottomHint        //最低层显示
                                    |Qt::Tool                           //不在任务栏显示
                                     );
//    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(showsnow()));
    connect(m_SystrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showRMouse()));

    getScreenInfo();

    m_qp.setX(0);
    m_qp.setY(0);

    qsrand(time(NULL));

    int i = 0;
    for(; i < MAX_SNOW_IMG; ++i)
    {
        m_snow[i].m_speed = qrand() % 5;
        if(m_snow[i].m_speed == 0)
            m_snow[i].m_speed = 1;

        m_snow[i].m_label.setFixedSize(30, 30);
        m_snow[i].m_label.setScaledContents(true);

        m_snow[i].m_path = ":/PixmapRes/" + QString::number(i/3) + ".png";

        m_snow[i].m_pixmap.load(m_snow[i].m_path);

        m_snow[i].m_label.setPixmap(m_snow[i].m_pixmap);

        qDebug() << m_snow[i].m_path;

        m_snow[i].m_label.setAttribute(Qt::WA_TranslucentBackground, true);
        m_snow[i].m_label.setWindowFlags(Qt::FramelessWindowHint        //去边框
                                        |Qt::X11BypassWindowManagerHint     //linux下脱离任务管理器
                                        |Qt::WindowStaysOnBottomHint        //最低层显示
                                        |Qt::Tool                           //不在任务栏显示
                                         );

        int x = qrand() % this->m_sW;

        m_snow[i].m_qp.setX(x);
        m_snow[i].m_qp.setY(0);

        m_snow[i].m_label.show();

        m_snow[i].m_label.move(m_snow[i].m_qp);


    }

    m_id = startTimer(20);
}

void test::setAttr(QList<QLabel> &label, QList<QPixmap> &pixmap)
{


}

void test::showsnow()
{

}

void test::timerEvent(QTimerEvent *event)
{
    int i = 0;
    int t_y = 0;
    for(; i < MAX_SNOW_IMG; ++i)
    {

        t_y = m_snow[i].m_qp.y();
        if(t_y >= m_sH)
        {
            m_snow[i].m_speed = qrand() % 5;
            if(m_snow[i].m_speed == 0)
                m_snow[i].m_speed = 1;
            int x = qrand() % this->m_sW;
            m_snow[i].m_qp.setX(x);
            t_y = 0;
        }
        else
        {
            t_y = m_snow[i].m_speed + t_y;
        }

        m_snow[i].m_qp.setY(t_y);
        m_snow[i].m_label.move(m_snow[i].m_qp);

        m_snow[i].m_matrix.rotate(1);
        m_snow[i].m_label.setPixmap(QPixmap(m_snow[i].m_path).transformed(m_snow[i].m_matrix, Qt::SmoothTransformation));
   }
}

void test::getScreenInfo()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();

    m_sW = screenRect.width();
    m_sH = screenRect.height();

}

void test::setSnowNextPistion(snow &s)
{

    qDebug() << "X = " << s.m_qp.x();
    qDebug() << "Y = " << s.m_qp.y();
}

void test::showRMouse(QSystemTrayIcon::ActivationReason event)
{
    qDebug() << "鼠标右击了";

    m_menu[0]->show();

    connect(m_action[0], SIGNAL(triggered(bool)), this, SLOT(snowexit()));
    connect(m_action[1], SIGNAL(triggered(bool)), this, SLOT(snowtop()));
    connect(m_action[2], SIGNAL(triggered(bool)), this, SLOT(showabout()));

    connect(m_action[2], SIGNAL(triggered(bool)), this, SLOT(showabout()));
}

void test::snowexit()
{
    qDebug() << "exit";
    ::exit(0);
}

void test::snowtop()
{
    qDebug() << "snowtop";
    if(m_action[1]->text() == "雪花在屏幕最前")
    {
        m_action[1]->setText("取消最前");
        setWindowFlags(windowFlags() &~ Qt::WindowStaysOnTopHint);
  //      showNormal();
  //      this->show();
    }
    else
    {
        m_action[1]->setText("雪花在屏幕最前");
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
   //     showNormal();
   //     this->show();
    }
    m_menu[0]->addAction(m_action[1]);
    m_menu[0]->show();
}

void test::showabout()
{
    this->ab->show();
}

void test::closeEvent(QCloseEvent *e)
{
}

test::~test()
{
 //   delete ql;
    delete ui;
}


