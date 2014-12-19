#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDir>
#include <QStringList>
#include <QDebug>

#include "aboutwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Translator(new QTranslator(this)),
    m_MenuFile(new QMenu(this)),
    m_MenuLanguages(new QMenu(this)),
    m_MenuHelp(new QMenu(this))
{
    ui->setupUi(this);

    // get the local language and load the translator with that
    m_Translator->load("tr_"+ QLocale::system().name(), "translations");
    qApp->installTranslator(m_Translator);

    // create the menus
    CreateMenuFile();
    CreateMenuLanguages();
    CreateMenuHelp();

    // translate whatever it's necessary
    retranslateUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    QMessageBox msg;

    msg.setWindowTitle(tr("Nuovo Oggetto"));
    msg.setText(tr("Ho creato un nuovo oggetto"));
    msg.exec();
}

void MainWindow::setNewLang(QAction *act)
{
    // install a new translator when the language changes
    QString lang = act->data().toString();
    QString qmPath(QDir("translations").absolutePath());

    m_Translator->load("tr_" + lang, qmPath);
    qApp->installTranslator(m_Translator);

    // retranslate whatever it's necessary
    retranslateUi();
}

void MainWindow::openAboutWindow()
{
    AboutWindow *w = new AboutWindow(this);
    w->show();
}

void MainWindow::CreateMenuFile()
{
    ui->menuBar->addMenu(m_MenuFile);

    m_MenuFileNew = new QAction(this);
    m_MenuFileNew->setShortcut(QKeySequence::New);
    connect(m_MenuFileNew, SIGNAL(triggered()), this, SLOT(newFile()));
    m_MenuFile->addAction(m_MenuFileNew);

    m_MenuFileExit = new QAction(this);
    m_MenuFileExit->setShortcut(QKeySequence::Close);
    connect(m_MenuFileExit, SIGNAL(triggered()), this, SLOT(close()));
    m_MenuFile->addAction(m_MenuFileExit);
}

void MainWindow::CreateMenuLanguages()
{
    ui->menuBar->addMenu(m_MenuLanguages);

    m_MenuLanguagesGrp = new QActionGroup(this);
    connect(m_MenuLanguagesGrp, SIGNAL(triggered(QAction*)), this, SLOT(setNewLang(QAction*)));

    QDir qmDir("translations");
    QStringList fileNames = qmDir.entryList(QStringList("tr_*.qm"));

    for (int i = 0; i < fileNames.size(); ++i)
    {
        QString lang = fileNames[i];

        lang.remove(0, lang.indexOf('_') + 1); // remove "tr_" substring
        lang.chop(3); // remove ".qm" substring

        QAction *act = new QAction(tr("%1 %2").arg(i + 1).arg(lang),this);
        act->setCheckable(true);
        act->setData(lang);

        m_MenuLanguages->addAction(act);
        m_MenuLanguagesGrp->addAction(act);

    }
}

void MainWindow::CreateMenuHelp()
{
    ui->menuBar->addMenu(m_MenuHelp);

    m_MenuHelpAbout = new QAction(this);
    connect(m_MenuHelpAbout, SIGNAL(triggered()), this, SLOT(openAboutWindow()));

    m_MenuHelp->addAction(m_MenuHelpAbout);

}

void MainWindow::retranslateUi()
{
    // translate all the widget "translatable"
    // create with Designer
    ui->retranslateUi(this);

    // translate all the widget
    // dynamically created
    m_MenuFile->setTitle(tr("&File"));
    m_MenuFileNew->setText(tr("&Nuovo"));
    m_MenuFileExit->setText(tr("&Esci"));
    m_MenuLanguages->setTitle(tr("Lingue"));
    m_MenuHelp->setTitle(tr("&Aiuto"));
    m_MenuHelpAbout->setText(tr("Info"));

    ui->statusBar->showMessage(tr("Io sono la barra di stato"));
}
