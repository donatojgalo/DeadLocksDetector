#ifndef PROCESS_H
#define PROCESS_H

#include <QString>

/**
  * @author Donato Galo
  * @param This class represents a system Process.
  *
  */
class Process {

	QString name;
	bool blocked;

public:
	Process() : name() {
		/* empty */
	}

	Process(QString _name) : name(_name), blocked(false) {
		/* empty */
	}

	Process(Process &process) : name(process.getName()), blocked(process.isBlocked()) {
		/* empty */
	}

	QString getName() {
		return name;
	}

	void setName(QString name) {
		this->name = name;
	}

	bool isBlocked() {
		return blocked;
	}

	void setBlocked(bool _blocked) {
		this->blocked = _blocked;
	}

	bool operator ==(Process &process) {
		return this->getName() == process.getName();
	}

};

#endif // PROCESS_H
