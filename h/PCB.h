/*
 * PCB.h
 *
 *  Created on: Apr 7, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include"Thread.h"


typedef int ID;
typedef unsigned int Time;

#define lock asm cli

#define unlock asm sti

class PCB {
public:

	enum State {New=1,Ready=2,Running=3,Blocked=4,Finished=5};

	PCB(unsigned long size,ID id,Time time);
	PCB();
	virtual ~PCB();

	static volatile PCB* runningThread;
	static PCB* mainThread;

	friend class Thread;
	static void interrupt timer(...);
	ID GetThreadID();
	State GetThreadState();



private:


	ID ThreadID;
	Thread * myThread;
	unsigned * myStack;
	unsigned Stack_OFF;
	unsigned Stack_SEG;
	unsigned BasePointer;
	unsigned long Stack_Size;

	int TimeSlice;
	//ID ThreadID;
	State ThreadState;



	static void WrapperFunction();




};



#endif /* PCB_H_ */
