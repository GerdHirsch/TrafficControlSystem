/*
 * Sensor.cpp
 *
 *  Created on: 16.07.2015
 *      Author: Gerd
 *      diese Sourcen sind in Verkehrssteuerung_SensorLib verwaltet
 */

#include <Sensor/ListenerMultiple.h>
#include <Sensor/ListenerSingleRawPointer.h>
#include <Sensor/Sensor.h>
#include <Sensor/SensorListener.h>

#include <iostream>
using namespace std;

namespace SH = SensorHersteller;

class MyListener : public SH::SensorListener{
public:
	MyListener(std::string const& name):name(name){}
	void trigger(unsigned long timestamp){
		std::cout << name << ".trigger() called" << std::endl;
	}
	virtual ~MyListener(){ std::cout << "MyListener::~MyListener(): " << name << std::endl;  }
	std::string name;
};

void demoSingleRawPointer(){
	cout << "============= demoSingleRawPointer()" << endl;
	typedef SH::Sensor<SH::ListenerSingleRawPointerPolicy> Sensor;

	Sensor s;
	MyListener l1("l1");
	MyListener l2("l2");
	s.addSensorListener(&l1);
	s.externalSignal();
	s.removeSensorListener(&l1);
	s.externalSignal();

	s.addSensorListener(&l2);
	s.externalSignal();

	s.addSensorListener(&l1);
	s.externalSignal();

}
void demoMultipleRawPointer(){
	cout << "============= demoMultipleRawPointer()" << endl;
	typedef SH::ListenerMultiple<SH::SensorListener*> ObserverPolicy;
	SH::Sensor<ObserverPolicy> s;
	MyListener l1("l1");
	MyListener l2("l2");
	s.addSensorListener(&l1);
	s.addSensorListener(&l2);

	s.externalSignal();

	s.removeSensorListener(&l1);

	s.externalSignal();
}

void demoMultipleSmartPointer(){
	cout << "============= demoMultipleSmartPointer()" << endl;

	typedef SH::SensorListener Listener;
	typedef std::shared_ptr<Listener> SharedPointer;
	typedef std::weak_ptr<Listener> WeakPointer;

	typedef SH::ListenerMultiple<WeakPointer> ObserverPolicy;
	typedef SH::Sensor<ObserverPolicy> Sensor;

	Sensor s;

	{
		cout << "WeakPointer einfügen, " << endl <<
				"der anschließend nicht mehr gültig ist" << endl;
		SharedPointer p(make_shared<MyListener>("listener"));
		// WeakPointer(SharedPointer p) ctor ist nicht explicit
		s.addSensorListener(p);
		cout << "externalSignal()" << endl;
		s.externalSignal();

	} //listener wird zerstört

	cout << "WeakPointer(p) nicht mehr gültig" << endl;
	cout << "externalSignal()" << endl;
	s.externalSignal();
	// keine Observer mehr vorhanden
	{
		cout << "2 WeakPointer einfügen" << endl <<
				"einen wieder entfernen!" << endl;
		SharedPointer p1(new MyListener("l1"));
		SharedPointer p2(new MyListener("l2"));

		s.addSensorListener(p1);
		s.addSensorListener(p2);

		cout << "externalSignal()" << endl;
		s.externalSignal();

		cout << "s.removeSensorListener(p1);" << endl;
		s.removeSensorListener(p1);
		//ein
		cout << "externalSignal()" << endl;
		s.externalSignal();
	} // l1 und l2 werden zerstört

	cout << "externalSignal()" << endl;
	s.externalSignal(); // kein gültiger WeakPointer vorhanden
}

int main(){
	cout << "Sensor" << endl;
	demoSingleRawPointer();
	demoMultipleRawPointer();
	demoMultipleSmartPointer();

}
