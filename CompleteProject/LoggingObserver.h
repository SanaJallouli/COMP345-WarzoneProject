#pragma once

#include <list>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class ILoggable  {
public :
	virtual string stringToLog()=0 ;
};
class Observer {
public:
	~Observer();
	virtual void Update(ILoggable*) = 0;
protected:
	Observer();
};
class LogObserver : public Observer {
public :
	LogObserver();
	void Update(ILoggable* logit) override;

};
class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify(ILoggable* logit);
	Subject();
	~Subject();
private:
	list<Observer*>* _observers;
};