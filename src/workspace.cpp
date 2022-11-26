#include "workspace.h"

Workspace::Workspace(DetectorData *_detectorData, MainWindow *parent) //
	: QWidget(parent), ui(new Ui::Workspace), mainWindow(parent), //
	  detectorData(_detectorData), ready(false) {

	ui->setupUi(this);
	connectSlots();
	initGui();

}

Workspace::~Workspace() {

	if (!ready) {
		setNullPointers();
	}
	delete lblA;
	delete lblS;
	delete lblE;
	delete lblD;
	delete tableA;
	delete tableS;
	delete arrayE;
	delete arrayD;
	delete matLayout;
	delete arrayLayout;
	delete vLayout;
	delete addActivityDialog;
	delete detectorExecutor;
	delete detectorData;
	delete ui;

}

void Workspace::setNullPointers() {

	lblA = NULL;
	lblS = NULL;
	lblE = NULL;
	lblD = NULL;
	tableA = NULL;
	tableS = NULL;
	arrayE = NULL;
	arrayD = NULL;
	matLayout = NULL;
	arrayLayout = NULL;
	vLayout = NULL;
	addActivityDialog = NULL;
	detectorExecutor = NULL;

}

void Workspace::connectSlots() {

	connect(ui->btnAddActivities, SIGNAL(clicked()), this, SLOT(addActivity()));
	connect(ui->btnProcess, SIGNAL(clicked()), this, SLOT(btnProcessClicked()));
	connect(ui->btnDetectDeadLocks, SIGNAL(clicked()), this, SLOT(detectDeadLocks()));

}

void Workspace::initGui() {

	ui->lblProcessesNum->setText(detectorData->getProcessesNumToString());
	ui->lblResourcesNum->setText(detectorData->getResourcesNumToString());
	ui->btnProcess->setEnabled(false);
	ui->btnDetectDeadLocks->setEnabled(false);
	ui->btnDetectDeadLocks->setVisible(false);

	vLayout = new QVBoxLayout();
	matLayout = new QHBoxLayout();
	arrayLayout = new QHBoxLayout();
	lblA = new QLabel("A =");
	lblS = new QLabel("S =");
	lblE = new QLabel("E =");
	lblD = new QLabel("D =");

	vLayout->addLayout(matLayout);
	vLayout->addLayout(arrayLayout);

	ui->widgetWorkspace->setLayout(vLayout);

}

bool Workspace::isReady() {
	return ready;
}

DetectorData *Workspace::getDetectorData() {
	return detectorData;
}

MainWindow *Workspace::getMainWindow() {
	return mainWindow;
}

void Workspace::setDetectorData(DetectorData *_detectorData) {
	this->detectorData = _detectorData;
}

void Workspace::addActivityInfo(Activity *activity) {
	activitiesList.append(activity);
	ui->listActivitiestInfo->addItem(activity->getActivityToString());
}

QList<Activity *> Workspace::getActivitiesList() {
	return activitiesList;
}

void Workspace::updateStatus() {
	ui->btnProcess->setEnabled(!activitiesList.isEmpty());
	mainWindow->setActionsEnable();
}

void Workspace::addActivity() {

	addActivityDialog = new AddActivityDialog(this);
	addActivityDialog->show();

}

void Workspace::btnProcessClicked() {

	try {
		process();
	} catch (const exception &e) {
		QMessageBox::information(
					this, "Deteccion de Interbloqueos", //
					"Algo salió mal!\nError: " //
					+ QString::fromStdString(e.what()));
	}



}

void Workspace::process() {

	if (activitiesList.isEmpty()) {
		return;
	}

	if (ready) {
		matLayout->removeWidget(tableA);
		matLayout->removeWidget(tableS);
		arrayLayout->removeWidget(arrayE);
		arrayLayout->removeWidget(arrayD);
		delete tableA;
		delete tableS;
		delete arrayE;
		delete arrayD;
	}

	ui->lblImage->setVisible(false);

	detectorExecutor = new DetectorExecutor(detectorData, activitiesList);
	detectorExecutor->execute();

	int *e = detectorExecutor->getE();
	int *d = detectorExecutor->getD();
	int **a = detectorExecutor->getA();
	int **s = detectorExecutor->getS();

	int numP = detectorData->getProcessesNum();
	int numR = detectorData->getResourcesNum();

	matLayout->addWidget(lblA);

	tableA = new QTableWidget(numP, numR);
	for (int i = 0; i < numP; i++) {
		for (int j = 0; j < numR; j++) {
			QTableWidgetItem *item = new QTableWidgetItem(QString::number(a[i][j]));
			tableA->setItem(i, j, item);
			tableA->setColumnWidth(j, SIZE);
		}
	}
	matLayout->addWidget(tableA);

	matLayout->addWidget(lblS);

	tableS = new QTableWidget(numP, numR);
	for (int i = 0; i < numP; i++) {
		for (int j = 0; j < numR; j++) {
			QTableWidgetItem *item = new QTableWidgetItem(QString::number(s[i][j]));
			tableS->setItem(i, j, item);
			tableS->setColumnWidth(j, SIZE);
		}
	}
	matLayout->addWidget(tableS);

	arrayLayout->addWidget(lblE);

	arrayE = new QTableWidget(1, numR);
	for (int i = 0; i < numR; i++) {
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(e[i]));
		arrayE->setItem(0, i, item);
		arrayE->setColumnWidth(i, SIZE);
	}
	arrayLayout->addWidget(arrayE);

	arrayLayout->addWidget(lblD);

	arrayD = new QTableWidget(1, numR);
	for (int i = 0; i < numR; i++) {
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(d[i]));
		arrayD->setItem(0, i, item);
		arrayD->setColumnWidth(i, SIZE);
	}
	arrayLayout->addWidget(arrayD);

	ui->btnDetectDeadLocks->setEnabled(true);
	ui->btnDetectDeadLocks->setVisible(true);

	ready = true;
	update();

}

void Workspace::detectDeadLocks() {

	QString msg = "";

	try {
		msg = detectorExecutor->detectDeadLocks() //
				? "El sistema esta libre de interbloqueos." //
				: "Se detectaron interbloqueos en los procesos:\n" //
				  + detectorExecutor->getDeadLocksProcess();
	} catch (const exception &e) {
		msg = "Algo salió mal!\nError: " + QString::fromStdString(e.what());
	}

	QMessageBox::information(this, "Deteccion de Interbloqueos", msg);

}
