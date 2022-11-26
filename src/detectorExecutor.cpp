#include "detectorExecutor.h"

DetectorExecutor::DetectorExecutor(DetectorData *_detectorData, QList<Activity *> _activitiesList) //
	: detectorData(_detectorData), activitiesList(_activitiesList) {
	/* empty */
}

DetectorExecutor::~DetectorExecutor() {

	if (activitiesList.isEmpty()) {
		return;
	}

	for (int i = 0; i < numPro; i++) {
		delete [] a[i];
		delete [] s[i];
	}

	delete [] a;
	delete [] s;
	delete [] e;
	delete [] d;

}

int *DetectorExecutor::getE() {
	return e;
}

int *DetectorExecutor::getD() {
	return d;
}

int **DetectorExecutor::getA() {
	return a;
}

int **DetectorExecutor::getS() {
	return s;
}

void DetectorExecutor::execute() {

	if (activitiesList.isEmpty()) {
		return;
	}

	resourcesList = detectorData->getResourcesList();
	processesList = detectorData->getProcessesList();

	numRes = resourcesList.size();
	numPro = processesList.size();

	e = new int[numRes];
	d = new int[numRes];

	for (int i = 0; i < numRes; i++) {
		int cap = resourcesList.at(i)->getCapacity();
		e[i] = cap;
		d[i] = cap;
	}

	a = new int *[numPro];
	s = new int *[numPro];

	for (int i = 0; i < numPro; i++) {
		a[i] = new int[numRes];
		s[i] = new int[numRes];
	}

	for (int i = 0; i < numPro; i++) {
		for (int j = 0; j < numRes; j++) {
			a[i][j] = 0;
			s[i][j] = 0;
		}
	}

	for (int i = 0; i < activitiesList.size(); i++) {

		Activity *activity = activitiesList.at(i);

		Process *process = activity->getProcess();
		QList<ResourceSelected *> resourcesSelectedList = activity->getResourcesSelectedList();
		ActivityType activityType = activity->getActivityType();

		int processIndex = processesList.indexOf(process);
		int tmp[numRes];
		bool blocked = true;

		for (int i = 0; i < numRes; i++) {
			tmp[i] = 0;
		}

		for (int i = 0; i < resourcesSelectedList.size(); i++) {

			ResourceSelected *resourceSelected = resourcesSelectedList.at(i);

			Resource *resource = resourceSelected->getResource();
			int resourceIndex = resourcesList.indexOf(resource);

			tmp[resourceIndex] = resourceSelected->getAmount();
			blocked = blocked && (resourceSelected->getAmount() <= d[resourceIndex]);

		}

		if (activityType == Request) {
			executeRequest(tmp, processIndex, blocked);
			process->setBlocked(!blocked);
		} else if (activityType == Liberate) {
			activity->setActivityType(Ignore);
			executeLiberate(tmp, processIndex);
		}


	}

}

bool DetectorExecutor::detectDeadLocks() {

	bool cont = false;

	QList<int> sortedIndexes = getSortedIndexes();
	/*for (int i = 0; i < sortedIndexes.size(); i++) {
		cout << endl << "index[" << i+1 << "] = " << sortedIndexes.at(i);
	}
	cout << endl;*/

	do {
		for (int i = 0; i < numPro; i++) {

			int index = sortedIndexes.at(i);

			if (index == -1) {
				continue;
			}

			Process *process = processesList.at(index);

			if (isLessThan(index) && !(reductionSequence.contains(process))) {

				for (int j = 0; j < numRes; j++) {
					d[j] += a[index][j];
				}

				reductionSequence.append(process);
				cont = true;

			} else {
				cont = false;
			}

		}
	} while (cont);

	printList(processesList, "* Processes List:");
	printList(reductionSequence, "* Reduction Sequence:");

	return compareLists();

}

QString DetectorExecutor::getDeadLocksProcess() {

	QString deadLocksProcess = "";

	for (int i = 0; i < numPro; i++) {

		Process *process = processesList.at(i);

		if (!reductionSequence.contains(process)) {
			deadLocksProcess.append(process->getName() + ", ");
		}

	}

	deadLocksProcess.remove(deadLocksProcess.size() - 2, 2);

	return deadLocksProcess;

}

void DetectorExecutor::executeRequest(int tmp[], int processIndex, bool blocked) {

	if (blocked) {

		for (int i = 0; i < numRes; i++) {
			a[processIndex][i] += tmp[i];
			d[i] -= tmp[i];
		}

	} else {

		for (int i = 0; i < numRes; i++) {
			s[processIndex][i] += tmp[i];
		}

	}

}

void DetectorExecutor::executeLiberate(int tmp[], int processIndex) {

	for (int i = 0; i < numRes; i++) {
		a[processIndex][i] -= tmp[i];
		d[i] += tmp[i];
	}

	execute();

}

bool DetectorExecutor::compareLists() {

	if (reductionSequence.isEmpty()) {
		return false;
	}

	bool ret = true;
	for (int i = 0; i < numPro; i++) {
		ret = ret && reductionSequence.contains(processesList.at(i));
	}
	return ret;

}

void DetectorExecutor::printList(QList<Process *> list, QString listName) {

	cout << endl << listName.toStdString();
	for (int i = 0; i < list.size(); i++) {
		cout << endl << "\tat(" << i+1 << ") = " //
			 << list.at(i)->getName().toStdString();
	}
	cout << endl;

}

bool DetectorExecutor::isLessThan(int index) {

	bool ret = true;
	for (int j = 0; j < numRes; j++) {
		ret = ret && (s[index][j] <= d[j]);
	}
	return ret;

}

QList<int> DetectorExecutor::getSortedIndexes() {

	QList<int> sortedIndexes;

	int lowerValue = -1;
	int idx = -1;
	int prevIndex = 0;

	for (int i = 0; i < numPro; i++) {

		int *index = findLowerRowIndex(lowerValue);
		lowerValue = index[1];

		if (sortedIndexes.contains(index[0])) {
			idx = prevIndex;
			prevIndex++;
		} else {
			idx = index[0];
		}

		sortedIndexes.append(idx);

	}

	return sortedIndexes;

}

int *DetectorExecutor::findLowerRowIndex(int lowerValue) {

	int aux = 0;
	int *lower = new int[2];
	lower[0] = -1;
	lower[1] = INT_MAX;

	for (int i = 0; i < numPro; i++) {

		aux = 0;
		for (int j = 0; j < numRes; j++) {
			aux += s[i][j];
		}

		if ((aux <= lower[1]) && (aux >= lowerValue)) {
			lower[0] = i;
			lower[1] = aux;
		}

	}

	return lower;

}
