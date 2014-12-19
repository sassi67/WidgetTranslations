#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newFile();
    void setNewLang(QAction *act);
    void openAboutWindow();

private:
    Ui::MainWindow *ui;
    QTranslator *m_Translator;

    QMenu *m_MenuFile;
    QMenu *m_MenuLanguages;
    QMenu *m_MenuHelp;

    QAction *m_MenuFileNew;
    QAction *m_MenuFileExit;

    QActionGroup *m_MenuLanguagesGrp;

    QAction *m_MenuHelpAbout;

    void CreateMenuFile();
    void CreateMenuLanguages();
    void CreateMenuHelp();
    void retranslateUi();
};

#endif // MAINWINDOW_H
