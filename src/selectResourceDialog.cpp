#include "selectResourceDialog.h"

SelectResourceDialog::SelectResourceDialog(AddActivityDialog *_parent, Activity *_activity) //
	: QDialog(_parent), ui(new Ui::SelectResourceDialog), parent(_parent), //
	  workspace(_parent->getWorkspace()), activity(_activity) {

	ui->setupUi(this);
	connectSlots();
	setData();

}

SelectResourceDialog::~SelectResourceDialog() {
	delete ui;
}

void SelectResourceDialog::connectSlots() {

	connect(this, SIGNAL(activityCreated()), parent, SLOT(emitActivityCreatedSignal()));
	connect(ui->boxResource, SIGNAL(currentIndexChanged(int)), this, SLOT(updateResourceCap()));
	connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addResource()));
	connect(ui->btnBack, SIGNAL(clicked()), this, SLOT(back()));
	connect(ui->btnAccept, SIGNAL(clicked()), this, SLOT(finish()));

}

void SelectResourceDialog::setData() {

	detectorData = workspace->getDetectorData();
	resourcesList = detectorData->getResourcesList();

	for (int i = 0; i < resourcesList.size(); i++) {
		ui->boxResource->addItem(resourcesList.at(i)->getName());
	}

}

void SelectResourceDialog::updateResourceCap() {

	ui->spinResourceNum->setValue(1);

	if (ui->boxResource->count() == 0) {
		ui->spinResourceNum->setEnabled(false);
		ui->btnAdd->setEnabled(false);
		return;
	}

	int max = resourcesList.at(ui->boxResource->currentIndex())->getCapacity();
	ui->spinResourceNum->setMaximum(max);

}

void SelectResourceDialog::addResource() {

	QString txt = "Recurso: " + ui->boxResource->currentText() //
			+ " / Cantidad: " + QString::number(ui->spinResourceNum->value());
	ui->boxSelectedResources->addItem(txt);

	for (int i = 0; i < resourcesList.size(); ++i) {
		Resource *resource = resourcesList.at(i);
		if (resource->getName() == ui->boxResource->currentText()) {
			activity->addResource(resource, ui->spinResourceNum->value());
		}
	}

	ui->boxResource->removeItem(ui->boxResource->currentIndex());

}

void SelectResourceDialog::back() {
	close();
	parent->show();
}

void SelectResourceDialog::finish() {

	if (ui->boxSelectedResources->count() == 0) {
		QMessageBox::information(this, "Informacion", //
								 "Por favor seleccione al menos un (1) recurso");
		return;
	}

	workspace->addActivityInfo(activity);
	emit activityCreated();
	close();

}
