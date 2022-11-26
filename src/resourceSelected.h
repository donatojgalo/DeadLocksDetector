#ifndef RESOURCESELECTED_H
#define RESOURCESELECTED_H

#include <resource.h>

/**
  * @author Donato Galo
  * @param This class represents a Resource requested by a Process.
  *
  */
class ResourceSelected {

	Resource *resource;
	int amount;

public:
	ResourceSelected(Resource *_resource, int _amount) //
		: resource(_resource), amount(_amount) {
		/* empty */
	}

	ResourceSelected(ResourceSelected &resourceSelected) //
		: resource(resourceSelected.getResource()), //
		amount(resourceSelected.getAmount()) {
		/* empty */
	}

	Resource *getResource() {
		return resource;
	}

	void setResource(Resource *_resource) {
		this->resource = _resource;
	}

	int getAmount() {
		return amount;
	}

	void setAmount(int _amount) {
		this->amount = _amount;
	}

};

#endif // RESOURCESELECTED_H
