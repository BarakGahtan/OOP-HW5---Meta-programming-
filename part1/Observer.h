//
// Created by Barak Gahtan on 31/08/2019.
//

#ifndef HW_5_NOA_BARAK_OBSERVER_H
#define HW_5_NOA_BARAK_OBSERVER_H
template <typename T>
class Observer{
public:
	virtual void handleEvent(const T&)=0;
	
	virtual ~Observer()= default;
	
};

#endif //HW_5_NOA_BARAK_OBSERVER_H
