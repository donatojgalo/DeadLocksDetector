#ifndef DETECTOREXECUTOR_H
#define DETECTOREXECUTOR_H

#include <iostream>
#include <limits.h>

#include <detectorData.h>
#include <activity.h>

using namespace std;

/**
  * @author Donato Galo
  * @param This class contains the deadlock detection logic.
  * Allows process a list of processes and resources with their interactions (activities),
  * and then detect the presence or absence of deadlocks.
  *
  */
class DetectorExecutor {

	DetectorData *detectorData;

	QList<Activity *> activitiesList;
	QList<Resource *> resourcesList;
	QList<Process *> processesList;
	QList<Process *> reductionSequence;

	int numRes;
	int numPro;

	int *e;
	int *d;
	int **a;
	int **s;

public:
	DetectorExecutor(DetectorData *_detectorData, QList<Activity *> _activitiesList);
	~DetectorExecutor();

	int *getE();
	int *getD();
	int **getA();
	int **getS();
	void execute();
	bool detectDeadLocks();
	QString getDeadLocksProcess();

private:
	void executeRequest(int tmp[], int processIndex, bool blocked);
	void executeLiberate(int tmp[], int processIndex);
	bool compareLists();
	void printList(QList<Process *> list, QString listName);
	bool isLessThan(int index);
	QList<int> getSortedIndexes();
	int *findLowerRowIndex(int lowerValue);

};

#endif // DETECTOREXECUTOR_H
