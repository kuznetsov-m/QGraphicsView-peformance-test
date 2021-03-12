#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(new Form(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}
