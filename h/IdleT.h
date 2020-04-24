/*
 * IdleT.h
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */

#ifndef IDLET_H_
#define IDLET_H_

#include "Thread.h"

class IdleT: public Thread {
public:
	IdleT(StackSize stackSize=defaultStackSize,Time timeSlice=defaultTimeSlice);
	virtual ~IdleT();

protected:

	virtual void run();
};

#endif /* IDLET_H_ */
