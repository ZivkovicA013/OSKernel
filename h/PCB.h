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

class PCBList;


class PCB {
public:

	enum State {New=1,Ready=2,Running=3,Blocked=4,Finished=5};

	PCB(unsigned long size,ID id,Time time);
	PCB();
	virtual ~PCB();

	static  PCB* runningThread;
	static void ReleaseAllPCB();
	static void interrupt timer(...);
	static PCB* mainThread;
	static PCB* idleThread;

	ID GetThreadID();
	State GetThreadState();
	void SetThreadState(State s);

	State ThreadState;

	int GetTimeToWait();
	void SetTimeToWait(int newT);

	friend class Thread;

private:

	int TimeSlice;
	unsigned * myStack;
	unsigned Stack_OFF;
	unsigned Stack_SEG;
	unsigned BasePointer;
	unsigned long Stack_Size;


	int TimeToWait;//Semaforsko vreme

	ID ThreadID;
	Thread * myThread;

	PCBList* PCBWaitingList;

	static void WrapperFunction();


};



#endif /* PCB_H_ */
