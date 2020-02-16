//
// Created by Barak Gahtan on 31/08/2019.
//

#ifndef HW_5_NOA_BARAK_SUBJECT_H
#define HW_5_NOA_BARAK_SUBJECT_H

#include "Observer.h"
#include "OOP5EventException.h"
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class Subject {
	vector<Observer<T>*> observers;

public:
	
	Subject()= default;
	
	~Subject() = default;
	
	void notify(const T &t) {
		for(int i = 0 ; i < observers.size() ; i++){
			observers[i]->handleEvent(t);
		}
	}
	
	void addObserver(Observer<T> &obs) {
		if(find(observers.begin(), observers.end(), &obs) != observers.end())
			throw ObserverAlreadyKnownToSubject();
		observers.push_back(&obs);
	}
	
	void removeObserver(Observer<T>& obs){
		if(find(observers.begin(), observers.end(), &obs) != observers.end()){
			observers.erase(find(observers.begin(), observers.end(), &obs));
			return;
		}else{
			throw ObserverUnknownToSubject();
		}
	}
	
	Subject<T>& operator+=(Observer<T>& obs){
		addObserver(obs);
		return *this;
	}
	
	Subject<T>& operator-=(Observer<T>& obs){
		removeObserver(obs);
		return *this;
	}
	
	Subject<T>& operator()(const T& t){
		notify(t);
		return *this;
	}
	
};

#endif //HW_5_NOA_BARAK_SUBJECT_H
