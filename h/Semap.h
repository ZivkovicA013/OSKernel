/*
 * Semap.h
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#ifndef SEMAP_H_
#define SEMAP_H_

#include"KerSem.h"

typedef unsigned int Time;


class Semaphore {
public:
	Semaphore(int init=1);

	virtual int wait(Time maxTimeToWait);
	virtual int signal(int n=0);

	int val () const;

	KernelSem* GetMyImpl();

	virtual ~Semaphore();

private:
	KernelSem* myImpl;

};

#endif /* SEMAP_H_ */
