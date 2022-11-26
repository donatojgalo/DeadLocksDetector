#ifndef CREATEDETECTORDIALOG_H
#define CREATEDETECTORDIALOG_H

#include <QDialog>

#include <ui_createDetectorDialog.h>
#include <mainWindow.h>
#include <workspace.h>
#include <detectorData.h>

namespace Ui {
class CreateDetectorDialog;
}

class MainWindow;
class Workspace;

/**
  * @author Donato Galo
  *
  */
class CreateDetectorDialog : public QDialog {
	Q_OBJECT
	
public:
	explicit CreateDetectorDialog(MainWindow *_mainWindow = 0);
	~CreateDetectorDialog();
	
private:
	Ui::CreateDetectorDialog *ui;
	MainWindow *mainWindow;
	DetectorData *detectorData;
	Workspace *workspace;
	QList<Resource *> resourcesList;

	void connectSlots();
	void showInfoWindow(const QString &info);

private slots:
	void addResource();
	void createDeadLockDetector();

};

#endif // CREATEDETECTORDIALOG_H
