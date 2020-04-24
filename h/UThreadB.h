/*
 * UThreadB.h
 *
 *  Created on: Apr 9, 2020
 *      Author: OS1
 */

#ifndef UTHREADB_H_
#define UTHREADB_H_

#include "Thread.h"

class UThreadB:public Thread{
private:


public:
	UThreadB(StackSize stackSize=defaultStackSize,Time timeSlice=defaultTimeSlice);
	virtual ~UThreadB();

protected:

	virtual void run();
};

#endif /* UTHREADB_H_ */
