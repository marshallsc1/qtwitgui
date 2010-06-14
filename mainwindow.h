/************************************************************************************
*
*   - QtWitGui -				2010 giantpune
*
*   the multilingual, multiplatform, multiformat gui for messing with
*   Wii game images.
*
*   This software comes to you with a GPLv3 license.
*   http://www.gnu.org/licenses/gpl-3.0.html
*
*   Basically you are free to modify this code, distribute it, use it in
*   other projects, or anything along those lines.  Just make sure that any
*   derivative work gets the same license.  And don't remove this notice from
*   the derivative work.
*
*   And please, don't be a douche.  If you borrow code from here, don't claim
*   you wrote it.  Share your source code with others.  Even if you are
*   charging a fee for the binaries, let others read the code as somebody has
*   done for you.
*
*************************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMutex>
#include <QProcess>
#include <QTreeWidget>
#include <QtDebug>
#include <QObject>
#include <QMenu>
#include <QAction>
#include <qpushbutton.h>

#include "wiitreethread.h"


typedef char			s8;
typedef short			s16;
typedef long			s32;
typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long	u64;

namespace Ui
{
    class MainWindow;
}

enum
{
    witNoJob = 0,
    witGetVersion,
    witCopy,
    witIlist,
    witDump
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void AddText( const char in[] );
    void SetStatus( const char str[] );
    void UpdateEffects();

//protected:
//    void contextMenuEvent(QContextMenuEvent *event);

private:
    //mutable QMutex mutex;
    Ui::MainWindow *ui;
    QProcess *witProcess;

    //for the edit tab
    QIcon groupIcon;
    QIcon keyIcon;
    QString filepaths;
    QString isoPath;
    QString lastPathLoadedCorrectly;
    QString witVersionString;
    QAction *extractAct;
    QAction *replaceAct;
    QStringList extractPaths;
    QStringList replacePaths;
    WiiTreeThread *wiithread;


    u8 tmdIOS;
    bool undoLastTextOperation;
    u8 witJob;
    //bool gameIsLoadedOk;

    char id[ 7 ];
    char name[ 0x40 ];

    //void ParseFileList();
    void DoIlist();
    QString ItemToFullPath( QTreeWidgetItem * item );
    bool SaveSettings();
    bool LoadSettings();
    void ResizeGuiToLanguage();



private slots:

    void on_checkBox_defaultRegion_clicked();
    void on_checkBox_defaultIos_clicked();
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();
    void on_pushButton_settings_searchPath_clicked();
    void on_save_pushButton_clicked();
    void on_pushButton_2_clicked();
    //void on_edit_img_pushButton_clicked();
    //void on_lineEdit_editingFinished();
    void on_checkBox_7_clicked();
    void on_checkBox_6_clicked();
    //void on_toolButton_2_clicked();
    //void on_pushButton_4_clicked();
    //void on_toolButton_clicked();
    void on_pushButton_3_clicked();
    void UpdateOptions();
    void ReadyReadStdOutSlot();
    void ProcessFinishedSlot( int, QProcess::ExitStatus );
    void ExtractSlot();
    void ReplaceSlot();

    // get output from a thread used to make a filetree
    void UpdateProgressFromThread( int );
    void ThreadIsDoneRunning( QTreeWidgetItem * );


public slots:
    void ShowMessage( const QString & );
    //void GetThreadDone( int );

signals:
    // send a kill message to the external running process
    void KillProcess();
};



#endif // MAINWINDOW_H
