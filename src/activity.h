#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QList>

#include <process.h>
#include <resourceSelected.h>

enum ActivityType {
	Request,
	Liberate,
	Ignore
};

/**
  * @author Donato Galo
  * @param This class represents an activity of a Process, which can be Request or Liberate one or more Resources.
  *
  */
class Activity {

	Process *process;
	QList<ResourceSelected *> resourcesSelectedList;
	ActivityType activityType;

public:
	Activity() {
		/* empty */
	}

	Activity(Activity &activity) //
		: process(activity.getProcess()), //
		  resourcesSelectedList(activity.getResourcesSelectedList()), //
		  activityType(activity.getActivityType()) {
		/* empty */
	}

	Process *getProcess() {
		return process;
	}

	void setProcess(Process *_process) {
		this->process = _process;
	}

	QList<ResourceSelected *> getResourcesSelectedList() {
		return resourcesSelectedList;
	}

	void setResourcesSelectedList(QList<ResourceSelected *> _resourcesSelectedList) {
		this->resourcesSelectedList = _resourcesSelectedList;
	}

	ActivityType getActivityType() {
		return activityType;
	}

	QString getActivityTypeToString() {

		QString type = "";

		switch(activityType) {
		case Request:
			type = "Solicita";
			break;
		case Liberate:
			type = "Libera";
			break;
		default:
			break;
		}

		return type;

	}

	void setActivityType(ActivityType _activityType) {
		this->activityType = _activityType;
	}

	void addResource(ResourceSelected *resourceSelected) {
		resourcesSelectedList.append(resourceSelected);
	}

	bool removeResource(ResourceSelected *resourceSelected) {
		return resourcesSelectedList.removeOne(resourceSelected);
	}

	void addResource(Resource *resource, int amount) {
		ResourceSelected *resourceSelected = new ResourceSelected(resource, amount);
		resourcesSelectedList.append(resourceSelected);
	}

	void removeResource(Resource *resource) {

		for (int i = 0; i < resourcesSelectedList.size(); i++) {
			ResourceSelected *resourceSelected = resourcesSelectedList.at(i);
			if (resourceSelected->getResource()->getName() == resource->getName()) {
				resourcesSelectedList.removeAt(i);
			}
		}

	}

	QString getActivityToString() {

		QString activity = process->getName() + ": " + getActivityTypeToString() + "(";

		for (int i = 0; i < resourcesSelectedList.size(); i++) {

			ResourceSelected *resourceSelected = resourcesSelectedList.at(i);

			activity.append(resourceSelected->getResource()->getName() //
					 + "[" + QString::number(resourceSelected->getAmount()) + "]");

			if ((resourcesSelectedList.size() > 1) //
					&& ((i + 1) != resourcesSelectedList.size())) {
				activity.append(", ");
			}

		}

		activity.append(")");
		return activity;

	}

};

#endif // ACTIVITY_H
