/*
 * Thread.cpp
 *
 *  Created on: Apr 7, 2020
 *      Author: OS1
 */
#include<stdio.h>

#include "Thread.h"
#include "SCHEDULE.H"
#include "System.h"


#define lock asm cli
#define unlock asm sti

volatile int Thread::CS_req=0;
ID Thread::myID=0;

Thread::Thread(StackSize stackSize,Time timeSlice) {

	Thread::myID++;
	this->myPCB=new PCB(stackSize,Thread::myID,timeSlice);
	this->myPCB->myThread=this;

	//Treba napraviti internu listu aktivnih niti
}
Thread::Thread(int a){

	//Ovo je main nit,zato dobija prazan konstruktor
	this->myPCB=new PCB();
	this->myPCB->myThread=this;
	PCB::mainThread=this->myPCB;
	PCB::runningThread=this->myPCB;

}


ID Thread::getId(){

	return this->myPCB->ThreadID;

}
void Thread::SetUpMainThread(){
	Thread(1);

}
void Thread::start(){

	PCB::State ready=2;
	this->myPCB->ThreadState=ready;
	System::List->AddNode(this->myPCB);
	Scheduler::put(this->myPCB);

}

ID Thread::gerRunnningId(){
	return PCB::mainThread->GetThreadID();

}
Thread* Thread::getThreadById(ID id){
	PCB * ret_pcb=System::List->GetByID((int)id);
	return ret_pcb->myThread;

}
void dispatch(){


		lock;
		Thread::CS_req=1;
		PCB::timer();
		unlock;
}
Thread::~Thread() {

}



