/*
 * KerrSem.h
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

typedef unsigned int Time;

#include "PCBList.h"

class KernelSem {
public:
	KernelSem(int init);
	virtual ~KernelSem();

	int wait(Time maxTimeToWait);
	int signal(int n=0);

	int val();

	PCBList* GetTimeBlocked();
	PCBList* GetValueBlocked();

	int GetMyId();

private:

	int sem_val;
	int myID;

	static int cntID;

	PCBList* timeBlocked;
	PCBList* valueBlocked;

	void FreeOneValueBlocked();
	int FreeNValueBlocked(int n);
};

#endif /* KERSEM_H_ */
