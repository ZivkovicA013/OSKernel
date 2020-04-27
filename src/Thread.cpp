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

}
Thread::Thread(int a){

	this->myPCB=new PCB();
	this->myPCB->myThread=this;
	PCB::runningThread=this->myPCB;
	PCB::runningThread->SetThreadState(PCB::Running);
	PCB::runningThread->ThreadState=PCB::Running;

}

ID Thread::getId(){

	return this->myPCB->ThreadID;

}
void Thread::SetUpMainThread(){
	new Thread(1);
}

void Thread::start(){
	lock;
	this->myPCB->ThreadState=PCB::Ready;
	System::List->AddNode(this->myPCB);
	Scheduler::put(this->myPCB);
	unlock;
}
void Thread::waitToComplete(){
	lock;


	if(this->myPCB==PCB::runningThread || this->myPCB->ThreadState==PCB::Finished){
		unlock;
		return;
	}


	PCB::runningThread->ThreadState=PCB::Blocked;
	this->myPCB->PCBWaitingList->AddNode((PCB*)PCB::runningThread);
	unlock;
	dispatch();
}

ID Thread::getRunnningId(){
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


	if(this->myPCB->ThreadState==0 || this->myPCB->ThreadID==1)
		return;
	this->waitToComplete();
	delete this->myPCB;

}


