#include "createDetectorDialog.h"

CreateDetectorDialog::CreateDetectorDialog(MainWindow *_mainWindow) //
	: QDialog(_mainWindow), ui(new Ui::CreateDetectorDialog), //
	mainWindow(_mainWindow), resourcesList() {

	ui->setupUi(this);
	connectSlots();

}

CreateDetectorDialog::~CreateDetectorDialog() {
	delete ui;
}

void CreateDetectorDialog::connectSlots() {

	connect(ui->btnAddResource, SIGNAL(clicked()), this, SLOT(addResource()));
	connect(ui->btnAceptar, SIGNAL(clicked()), this, SLOT(createDeadLockDetector()));

}

void CreateDetectorDialog::showInfoWindow(const QString &info) {
	QMessageBox::information(this, tr("Informacion"), info);
}

void CreateDetectorDialog::addResource() {

	QString name = "R" + QString::number(ui->spinResourcesNum->text().toInt() + 1);

	int cap = ui->spinResourcesCap->value();

	Resource *resource = new Resource(name, cap);
	resourcesList.append(resource);

	ui->spinResourcesNum->setValue(ui->spinResourcesNum->value() + 1);
	ui->spinResourcesCap->setValue(1);

}

void CreateDetectorDialog::createDeadLockDetector() {

	if (ui->spinProcessesNum->value() == 0) {
		showInfoWindow("La cantidad de procesos debe ser mayor a cero");
		return;
	}
	if (ui->spinResourcesNum->value() == 0) {
		showInfoWindow("La cantidad de recursos debe ser mayor a cero");
		return;
	}

	QList<Process *> processesList;

	for (int i = 0; i < ui->spinProcessesNum->value(); i++) {

		QString name = "P" + QString::number(i + 1);

		Process *process = new Process(name);
		processesList.append(process);

	}

	detectorData = new DetectorData();
	detectorData->setResourcesList(resourcesList);
	detectorData->setProcessesList(processesList);

	workspace = new Workspace(detectorData, mainWindow);
	mainWindow->setWorkspaceWidget(workspace);

}
