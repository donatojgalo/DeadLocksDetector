#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) //
	: QMainWindow(parent), ui(new Ui::MainWindow), isWorking(false) {

	ui->setupUi(this);
	connectSlots();
	setActionsEnable();
	newFile();

}

MainWindow::~MainWindow() {

	if (isWorking) {
		delete workspace;
	}

	delete createDetectorDialog;
	delete ui;

}

void MainWindow::connectSlots() {

	connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
	connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeFile()));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui->actionAddActivity, SIGNAL(triggered()), this, SLOT(addActivity()));
	connect(ui->actionProcess, SIGNAL(triggered()), this, SLOT(process()));

}

void MainWindow::setWorkspaceWidget(Workspace *_workspace) {

	this->workspace = _workspace;
	setCentralWidget(workspace);
	createDetectorDialog->close();

	isWorking = true;
	setActionsEnable();

}

void MainWindow::setActionsEnable() {

	bool status = isWorking ? !workspace->getActivitiesList().isEmpty() : false;

	ui->menuTools->setEnabled(isWorking);
	ui->actionAddActivity->setEnabled(isWorking);
	ui->actionProcess->setEnabled(isWorking && status);
	ui->actionClose->setEnabled(isWorking);

}

void MainWindow::newFile() {

	if (isWorking) {

		if (QMessageBox::question(this, "DeadLocks Detector", //
								  "Desea cerrar el archivo actual?", //
								  QMessageBox::Yes | QMessageBox::No) //
				== QMessageBox::Yes) {
			closeFile();
		}

	}

	createDetectorDialog = new CreateDetectorDialog(this);
	createDetectorDialog->show();

}

void MainWindow::closeFile() {

	delete workspace;
	isWorking = false;
	setActionsEnable();

}

void MainWindow::closeEvent(QCloseEvent *evt) {

	if (!isWorking) {
		::exit(0);
	}

	if (QMessageBox::question(this, "DeadLocks Detector", //
							  "Esta seguro que desea cerrar la aplicacion?", //
							  QMessageBox::Yes | QMessageBox::No) //
			== QMessageBox::Yes) {
		closeFile();
		::exit(0);
	}

	evt->ignore();

}

void MainWindow::about() {

	QString txt = "Sistema para detectar interbloqueos entre procesos.\n\n";
	txt += "Desarrollado por Donato Galo.\n";
	txt += "Para la materia Sistemas Operativos.\n";
	txt += "Facultad de Ingenieria. Escuela de Sistemas.\n";
	txt += "Universidad de Los Andes.\n\n";
	txt += "Merida, 2012.";

	QMessageBox::about(this, "Acerca de DeadLocks Detector", txt);

}

void MainWindow::addActivity() {
	workspace->addActivity();
}

void MainWindow::process() {
	workspace->btnProcessClicked();
}
