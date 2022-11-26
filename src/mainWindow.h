#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include <ui_mainWindow.h>
#include <createDetectorDialog.h>
#include <workspace.h>

namespace Ui {
	class MainWindow;
}

class CreateDetectorDialog;

/**
  * @author Donato Galo
  *
  */
class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void setWorkspaceWidget(Workspace *_workspace);
	void setActionsEnable();

private:
	Ui::MainWindow *ui;
	bool isWorking;
	Workspace *workspace;
	CreateDetectorDialog *createDetectorDialog;

	void connectSlots();
	void closeEvent(QCloseEvent *evt);

private slots:
	void newFile();
	void closeFile();
	void about();
	void addActivity();
	void process();

};

#endif // MAINWINDOW_H
