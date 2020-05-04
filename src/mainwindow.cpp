#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QEvent>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QWhatsThis>
#include "drawingwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(800, 600);
	initWidgets();
    initMenus();

    m_statusLabel = new QLabel(this);
    m_statusLabel->setText("No tool selected.");
    statusBar()->addPermanentWidget(m_statusLabel);

    m_verticesLabel = new QLabel(this);
    m_verticesLabel->setText("Vertices:0");
    statusBar()->addPermanentWidget(m_verticesLabel);

    m_linesLabel = new QLabel(this);
    m_linesLabel->setText("Lines:0");
    statusBar()->addPermanentWidget(m_linesLabel);

}

MainWindow::~MainWindow() {
    // Intentionally empty
}

/**
  Initializes all menus of this widget.
*/
void MainWindow::initMenus() {
    // Creates the file menu
    m_fileMenu = new QMenu(this);
    m_fileMenu->setTitle(QString("&File"));
    menuBar()->addMenu(m_fileMenu);

    // Creates the quit action in the file menu
    m_quitAction = new QAction(this);
    m_quitAction->setMenuRole(QAction::QuitRole);
    m_quitAction->setText(QString("&Quit"));
    m_quitAction->setStatusTip(QString("Quits this application"));
    m_quitAction->setToolTip(QString("Quits this application"));
    m_quitAction->setWhatsThis(QString("Activate this item to quit this application. You will"
                                  " be asked for confirmation."));
    m_fileMenu->addAction(m_quitAction);

    // Connects the triggering of the quit action
    // to closing the main window
    connect(m_quitAction, SIGNAL(triggered()),
            this, SLOT(close()));    
    

    m_toolsMenu = new QMenu(this);
    m_toolsMenu->setTitle("&Tools");
    menuBar()->addMenu(m_toolsMenu);

    m_addVertexAction = new QAction(this);
    m_addVertexAction->setText("&Add vertex");
    m_toolsMenu->addAction(m_addVertexAction);
    connect(m_addVertexAction, SIGNAL(triggered()),
            this, SLOT(startAddingVertices()));

    m_moveVertexAction = new QAction(this);
    m_moveVertexAction->setText("&Move vertex");
    m_toolsMenu->addAction(m_moveVertexAction);
    connect(m_moveVertexAction, SIGNAL(triggered()),
            this, SLOT(startMovingVertices()));

    m_deleteVertexAction = new QAction(this);
    m_deleteVertexAction->setText("&Delete vertex");
    m_toolsMenu->addAction(m_deleteVertexAction);
    connect(m_deleteVertexAction, SIGNAL(triggered()),
            this, SLOT(startDeletingVertices()));

    m_addLineAction = new QAction(this);
    m_addLineAction->setText("&Add line");
    m_toolsMenu->addAction(m_addLineAction);
    connect(m_addLineAction, SIGNAL(triggered()),
            this, SLOT(startAddingLines()));

    m_deleteLineAction = new QAction(this);
    m_deleteLineAction->setText("&Delete line");
    m_toolsMenu->addAction(m_deleteLineAction);
    connect(m_deleteLineAction, SIGNAL(triggered()),
            this, SLOT(startDeletingLines()));


    // Create the help menu and its contents
    m_helpMenu = new QMenu(this);
    m_helpMenu->setTitle(QString("&Help"));
    menuBar()->addMenu(m_helpMenu);

    m_whatsThisAction = QWhatsThis::createAction(this);
    m_whatsThisAction->setText(QString("&Whats this?"));
    m_helpMenu->addAction(m_whatsThisAction);

    m_aboutAction = new QAction(this);
    m_aboutAction->setMenuRole(QAction::AboutQtRole);
    m_aboutAction->setText(QString("&About"));
    m_helpMenu->addAction(m_aboutAction);
    connect(m_aboutAction, SIGNAL(triggered()),
            qApp, SLOT(aboutQt()));

}

/**
  Translates all texts of this widget.
*/
void MainWindow::initWidgets() {
    setWindowTitle(QString("Drawing"));
    m_drawingWidget = new DrawingWidget(this);
    setCentralWidget(m_drawingWidget);
}

void MainWindow::startAddingVertices() {
    m_drawingWidget->setState(ADD_VERTEX_SELECTED);
    m_statusLabel->setText("Adding vertices");
}
void MainWindow::startMovingVertices() {
    if (m_drawingWidget->m_points.size() != 0){
        m_drawingWidget->setState(MOVE_VERTEX_SELECTED);
        m_statusLabel->setText("Moving vertices");
    }
}
void MainWindow::startDeletingVertices() {
    if (m_drawingWidget->m_points.size() != 0){
        m_drawingWidget->setState(DELETE_VERTEX_SELECTED);
        m_statusLabel->setText("Deleting vertices");
    }
}
void MainWindow::startAddingLines() {
    if (m_drawingWidget->m_points.size() >= 2){
        m_drawingWidget->setState(ADD_LINE_SELECTED);
        m_statusLabel->setText("Adding lines");
    }
}
void MainWindow::startDeletingLines() {
    if (m_drawingWidget->m_lines.size() != 0){
        m_drawingWidget->setState(DELETE_LINE_SELECTED);
        m_statusLabel->setText("Deleting lines");
    }
}

void MainWindow::updateVerticesLabel(){
    QString str1 = "Vertices:";
    QString str2 = QString::number(m_drawingWidget->m_points.size());
    str1.append(str2);
    m_verticesLabel->setText(str1);
}

void MainWindow::updateLinesLabel(){
    QString str1 = "Lines:";
    QString str2 = QString::number(m_drawingWidget->m_lines.size());
    str1.append(str2);
    m_linesLabel->setText(str1);
}

void MainWindow::setToolToNoTool(){
    m_statusLabel->setText("No tool selected.");
}
