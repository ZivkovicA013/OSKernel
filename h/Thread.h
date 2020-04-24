/*
 * Thread.h
 *
 *  Created on: Apr 7, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

#include"PCB.h"
#include"SCHEDULE.H"


typedef unsigned long StackSize;
const StackSize defaultStackSize=4096;
typedef unsigned int Time;
const Time defaultTimeSlice=2;
typedef int ID;

//Svaka nit mora da ima internu listu niti na....

class Thread {
public:

	void start();//Nit postaje Ready,njen pcb ide u scheduler
	void waitToComplete();
	virtual ~Thread();

	ID getId();//Dohvata id niti
	static ID gerRunnningId();
	static Thread * getThreadById(ID id);
	static void SetUpMainThread();
	static void SetUpIdleThread();
	static volatile int CS_req;





	Thread(StackSize stackSize=defaultStackSize,Time timeSlice=defaultTimeSlice);
	//treba da bude protected

protected:

	friend class PCB;
	virtual void run(){}
	PCB* myPCB;

private:

	Thread(int a);
	Thread(char a);

	static ID myID;

};

void dispatch();

#endif /* THREAD_H_ */
