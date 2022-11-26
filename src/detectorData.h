#ifndef DETECTORDATA_H
#define DETECTORDATA_H

#include <QList>

#include <process.h>
#include <resource.h>

/**
  * @author Donato Galo
  * @param This class contains the lists of Processes and Resources of the system.
  *
  */
class DetectorData {

	QList<Process *> processesList;
	QList<Resource *> resourcesList;

public:
	DetectorData() {
		/* empty */
	}

	DetectorData(DetectorData &detectorData) //
		: processesList(detectorData.getProcessesList()), //
		resourcesList(detectorData.getResourcesList()) {
		/* empty */
	}

	QList<Resource *> getResourcesList() {
		return resourcesList;
	}

	void setResourcesList(QList<Resource *> resourcesList) {
		this->resourcesList = resourcesList;
	}

	QList<Process *> getProcessesList() {
		return processesList;
	}

	void setProcessesList(QList<Process *> processesList) {
		this->processesList = processesList;
	}

	int getProcessesNum() {
		return processesList.size();
	}

	int getResourcesNum() {
		return resourcesList.size();
	}

	QString getProcessesNumToString() {
		return QString::number(processesList.size());
	}

	QString getResourcesNumToString() {
		return QString::number(resourcesList.size());
	}

};

#endif // DETECTORDATA_H
