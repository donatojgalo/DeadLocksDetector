#ifndef SELECTRESOURCEDIALOG_H
#define SELECTRESOURCEDIALOG_H

#include <QDialog>

#include <ui_selectResourceDialog.h>
#include <workspace.h>
#include <addActivityDialog.h>
#include <activity.h>

namespace Ui {
class SelectResourceDialog;
}

class Workspace;
class AddActivityDialog;

/**
  * @author Donato Galo
  *
  */
class SelectResourceDialog : public QDialog {
	Q_OBJECT
	
public:
	explicit SelectResourceDialog(AddActivityDialog *_parent, Activity *_activity);
	~SelectResourceDialog();
	
private:
	Ui::SelectResourceDialog *ui;
	AddActivityDialog *parent;
	Workspace *workspace;
	DetectorData *detectorData;
	QList<Resource *> resourcesList;
	Activity *activity;

	void connectSlots();
	void setData();

private slots:
	void updateResourceCap();
	void addResource();
	void back();
	void finish();

signals:
	void activityCreated();

};

#endif // SELECTRESOURCEDIALOG_H
