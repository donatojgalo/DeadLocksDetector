#include "addActivityDialog.h"

AddActivityDialog::AddActivityDialog(Workspace *_workspace) //
	: QDialog(_workspace), ui(new Ui::AddActivityDialog), workspace(_workspace) {

	ui->setupUi(this);
	connectSlots();
	setData();
	selectResourceDialog = NULL;

}

AddActivityDialog::~AddActivityDialog() {

	if (selectResourceDialog != NULL) {
		delete selectResourceDialog;
	}
	delete ui;

}

Workspace *AddActivityDialog::getWorkspace() {
	return workspace;
}

void AddActivityDialog::connectSlots() {

	connect(this, SIGNAL(activityCreated()), workspace, SLOT(updateStatus()));
	connect(ui->btnNext, SIGNAL(clicked()), this, SLOT(addSelectResource()));

}

void AddActivityDialog::setData() {

	detectorData = workspace->getDetectorData();
	processesList = detectorData->getProcessesList();

	for (int i = 0; i < processesList.size(); i++) {
		ui->boxProcess->addItem(processesList.at(i)->getName());
	}

}

ActivityType AddActivityDialog::getActivityType() {

	if (ui->btnRequest->isChecked()) {
		return Request;
	} else if (ui->btnLiberate->isChecked()) {
		return Liberate;
	} else {
		return Ignore;
	}

}

void AddActivityDialog::emitActivityCreatedSignal() {
	emit activityCreated();
}

void AddActivityDialog::addSelectResource() {

	Process *process = processesList.at(ui->boxProcess->currentIndex());

	Activity *activity = new Activity();
	activity->setProcess(process);
	activity->setActivityType(getActivityType());

	selectResourceDialog = new SelectResourceDialog(this, activity);
	selectResourceDialog->show();

	close();

}
