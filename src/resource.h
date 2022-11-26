#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>

/**
  * @author Donato Galo
  * @param This class represents a system Resource.
  *
  */
class Resource {

	QString name;
	int capacity;

public:
	Resource() : name(), capacity(1) {
		/* empty */
	}

	Resource(QString _name, int _capacity) //
		: name(_name), capacity(_capacity) {
		/* empty */
	}

	Resource(Resource &resource) //
		: name(resource.getName()), //
		capacity(resource.getCapacity()) {
		/* empty */
	}

	QString getName() {
		return name;
	}

	void setName(QString name) {
		this->name = name;
	}

	int getCapacity() {
		return capacity;
	}

	void setCapacity(int capacity) {
		this->capacity = capacity;
	}

	bool operator ==(Resource &resource) {
		return (this->getName() == resource.getName()) //
				&& (this->getCapacity() == resource.getCapacity());
	}

};

#endif // RESOURCE_H
