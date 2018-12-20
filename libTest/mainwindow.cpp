﻿#include <QLabel>
#include <QDebug>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ui_AeroClientWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : MuCustomWindow(parent)
    , ui(new Ui::MainWindow)
    , aeroUI(new Ui::AeroCLientWidget)
{
    setWindowTitle("Test Custom Window");
    resize(800, 600);

    QWidget *pClientWidget = new QWidget(this);
    ui->setupUi(pClientWidget);

    this->titleBar()->setTitleHeight(50);
    this->titleBar()->setObjectName("titleBar");
    this->titleBar()->titleLabel()->setObjectName("titleLabel");
    this->titleBar()->minimizeButton()->setObjectName("minimizeButton");
    this->titleBar()->maximizeButton()->setObjectName("maximizeButton");
    this->titleBar()->closeButton()->setObjectName("closeButton");
    setClientWidget(pClientWidget);
    const QString buttonStyle = "QPushButton {  \
                                    border: none; \
                                    background-color: #52baff; \
                                    width: 80px; \
                                    height: 30px; \
                                 } \
                                 QPushButton::pressed { \
                                    background-color: gray; \
                                 }";
    MuCustomMessageBox::setTitleStyleSheet(QStringLiteral("QLabel { color: black }"));
    MuCustomMessageBox::setButtonStyleSheet(QDialogButtonBox::Ok, buttonStyle);

    connect(ui->dialogBtn, &QPushButton::clicked, this, &MainWindow::onDialogBtnClicked);
    connect(ui->informationBtn, &QPushButton::clicked, this, &MainWindow::onInformationBtnClicked);
    connect(ui->errorBtn, &QPushButton::clicked, this, &MainWindow::onErrorBtnClicked);
    connect(ui->successBtn, &QPushButton::clicked, this, &MainWindow::onSuccessBtnClicked);
    connect(ui->warningBtn, &QPushButton::clicked, this, &MainWindow::onWarningBtnClicked);
#ifdef Q_OS_WIN32
    initAreoWindow();
    connect(ui->aeroBtn, &QPushButton::clicked, m_AeroWindow, &MuWinAeroShadowWindow::show);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_AeroWindow;
}

void MainWindow::onDialogBtnClicked()
{
    MuCustomDialog dialog;
    QLabel label("This is a Custom Dialog!");
    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    dialog.titleBar()->titleLabel()->setObjectName("dialogTitleLabel");
    dialog.setModal(true);
    dialog.setWindowTitle("dialog");
    dialog.setClientWidget(&label);
    dialog.exec();
}

void MainWindow::onInformationBtnClicked()
{
    MuCustomMessageBox::showInformation(nullptr,
                                        QStringLiteral("Information!"),
                                        QStringLiteral("This is a Information MessageBox!"));
}

void MainWindow::onErrorBtnClicked()
{
    MuCustomMessageBox::showError(nullptr,
                                  QStringLiteral("Error!"),
                                  QStringLiteral("This is a Error MessageBox!"));
}

void MainWindow::onSuccessBtnClicked()
{
    MuCustomMessageBox::showSuccess(nullptr,
                                    QStringLiteral("Success!"),
                                    QStringLiteral("This is a Success MessageBox!"));
}

void MainWindow::onWarningBtnClicked()
{
    MuCustomMessageBox::showWarning(nullptr,
                                    QStringLiteral("Warning!"),
                                    QStringLiteral("This is a Warning MessageBox!"));
}

void MainWindow::initAreoWindow()
{
    m_AeroWindow = new MuWinAeroShadowWindow;
    m_AeroWindow->setRubberBandOnMove(true);
    m_AeroWindow->setRubberBandOnResize(true);
    m_AeroWindow->setWindowTitle(QStringLiteral("Test Aero Window"));
    m_AeroWindow->titleBar()->setObjectName("aeroTitleBar");
    QWidget *pClientWidget = new QWidget(m_AeroWindow);
    aeroUI->setupUi(pClientWidget);
    m_AeroWindow->setClientWidget(pClientWidget);
}

