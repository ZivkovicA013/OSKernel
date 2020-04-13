/*
 * UThreadA.h
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */

#ifndef UTHREADA_H_
#define UTHREADA_H_

#include "Thread.h"

class UThreadA:public Thread{
public:
	UThreadA(StackSize stackSize=defaultStackSize,Time timeSlice=defaultTimeSlice);
	virtual ~UThreadA();

protected:

	virtual void run();
};

#endif /* UTHREADA_H_ */
