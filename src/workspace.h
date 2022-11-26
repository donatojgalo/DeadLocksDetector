#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>

#include <exception>

#include <ui_workspace.h>
#include <mainWindow.h>
#include <detectorData.h>
#include <detectorExecutor.h>
#include <activity.h>
#include <addActivityDialog.h>

const int SIZE = 30;

namespace Ui {
class Workspace;
}

class MainWindow;
class AddActivityDialog;

/**
  * @author Donato Galo
  * @param This class represents the communication layer between logic and system interface.
  *
  */
class Workspace : public QWidget {
	Q_OBJECT

public:
	explicit Workspace(DetectorData *_detectorData, MainWindow *parent = 0);
	~Workspace();

	bool isReady();
	DetectorData *getDetectorData();
	MainWindow *getMainWindow();
	void setDetectorData(DetectorData *_detectorData);
	void addActivityInfo(Activity *activity);
	QList<Activity *> getActivitiesList();

private:
	Ui::Workspace *ui;
	MainWindow *mainWindow;
	DetectorData *detectorData;
	DetectorExecutor *detectorExecutor;
	AddActivityDialog *addActivityDialog;
	QList<Activity *> activitiesList;
	bool ready;

	QVBoxLayout *vLayout;
	QHBoxLayout *matLayout;
	QHBoxLayout *arrayLayout;
	QLabel *lblA;
	QLabel *lblS;
	QLabel *lblE;
	QLabel *lblD;
	QTableWidget *tableA;
	QTableWidget *tableS;
	QTableWidget *arrayE;
	QTableWidget *arrayD;

	void setNullPointers();
	void connectSlots();
	void initGui();
	void showArrayData(int *array);
	void showMatrizData(int **matriz);

public slots:
	void updateStatus();
	void addActivity();
	void btnProcessClicked();

private slots:
	void process();
	void detectDeadLocks();

};

#endif // WORKSPACE_H
