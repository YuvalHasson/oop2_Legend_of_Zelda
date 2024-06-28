#pragma once

#include "LinkObserver.h"

class LinkSubject{

public:
	virtual ~LinkSubject() = default;
    virtual void RegisterObserver(LinkObserver* observer) = 0;

	virtual void RemoveObserver(LinkObserver* observer) = 0;

	virtual void NotifyObserversLinkOut() const = 0;

	virtual void NotifyObservers() = 0;

};