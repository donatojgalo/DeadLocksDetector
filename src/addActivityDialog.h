#ifndef ADDACTIVITYDIALOG_H
#define ADDACTIVITYDIALOG_H

#include <QDialog>

#include <ui_addActivityDialog.h>
#include <selectResourceDialog.h>
#include <workspace.h>

namespace Ui {
class AddActivityDialog;
}

class Workspace;
class SelectResourceDialog;

/**
  * @author Donato Galo
  *
  */
class AddActivityDialog : public QDialog {
	Q_OBJECT

public:
	explicit AddActivityDialog(Workspace *_workspace);
	~AddActivityDialog();

	Workspace *getWorkspace();

private:
	Ui::AddActivityDialog *ui;
	SelectResourceDialog *selectResourceDialog;
	Workspace *workspace;
	DetectorData *detectorData;
	QList<Process *> processesList;

	void connectSlots();
	void setData();
	ActivityType getActivityType();

public slots:
	void emitActivityCreatedSignal();

private slots:
	void addSelectResource();

signals:
	void activityCreated();

};

#endif // ADDACTIVITYDIALOG_H
