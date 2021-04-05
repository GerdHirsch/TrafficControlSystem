

//#include "../include/ModelBuilder.hpp"
//#include "../include/HardwareFactory.hpp"
#include <TCS/ModelBuilder.hpp>
#include <TCS/HardwareFactory.hpp>

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

template<class Selectors>
void printSelectors(Selectors &selectors){
	cout << "=======================" << endl;
	for(auto selector : selectors)
		cout << selector << endl;
	cout << "=======================" << endl;
}

void demoCrossRoadInteractive(){
	cout << __PRETTY_FUNCTION__ << endl;
	using Factory = TCS::HardwareFactory;
	using Builder = TCS::ModelBuilder<Factory>;

	using CrossRoad = Builder::CrossRoad;
	CrossRoad::printout = true;

	Factory factory;
	Builder builder(factory);
	auto &crossRoad = builder.getCrossRoad();
	auto &sensor = builder.getSensor();

	string selector;
	const string selectors[] = {
			"quit", "off", "on", "flash", "regulate", "defect"
	};
	enum {quit, off, on, flash, regulate, defect};


	do{
		printSelectors(selectors);
		cout << "Select: ";
		cin >> selector;
		cout << "selector: " << selector << endl;
		if(selector == selectors[off]){
			crossRoad.off();
		} else if(selector == selectors[on]){
			crossRoad.on();
		} else if(selector == selectors[flash]){
			crossRoad.flash();
		} else if(selector == selectors[regulate]){
			sensor.externalSignal();
//			crossRoad.regulateTraffic();
		} else if(selector == selectors[defect]){
			crossRoad.defect();
		} else if(selector == selectors[quit]){
			// nothing to do
		}else{
			cout << "choose one provided:" << endl;
		}

	}while(selector != selectors[quit]);

	cout << "thanks for trying this demo" << endl;

}


