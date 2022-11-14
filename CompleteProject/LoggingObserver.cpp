#include "LoggingObserver.h"
#include <iostream>

Observer::~Observer()
{
}
Observer::Observer()
{
}
LogObserver::LogObserver() {
}

Subject::Subject() {
	_observers = new list<Observer*>;
}
Subject::~Subject() {
	delete _observers;
}
void Subject::Attach(Observer* o) {
	_observers->push_back(o);
};
void Subject::Detach(Observer* o) {
	_observers->remove(o);
};
void Subject::Notify(ILoggable* logit) {
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(logit);
};

void LogObserver::Update(ILoggable* logit)
{
	cout<<logit->stringToLog()<<endl;
}
