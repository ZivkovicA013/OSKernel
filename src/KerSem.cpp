/*
 * KerSem.cpp
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#include "KerSem.h"
#include "Thread.h"
#include <stdio.h>


int KernelSem::cntID=0;

KernelSem::KernelSem(int init) {
	// TODO Auto-generated constructor stub
	this->sem_val=init;
	this->timeBlocked=new PCBList();
	this->valueBlocked=new PCBList();
	this->myID=KernelSem::cntID;
	KernelSem::cntID++;

}

KernelSem::~KernelSem() {
		delete this->timeBlocked;
		delete this->valueBlocked;
}
int KernelSem::GetMyId(){
	return this->myID;
}
int KernelSem::wait(Time maxTimeToWait) {



	if(maxTimeToWait>0){
		asm cli;
		PCB::runningThread->SetThreadState(PCB::Blocked);
		this->timeBlocked->AddNode(PCB::runningThread);
		PCB::runningThread->SetTimeToWait(maxTimeToWait);
		asm sti;
		dispatch();
	}
	else if(maxTimeToWait==0){

		if(--this->sem_val<0){
			asm cli;
			PCB::runningThread->SetThreadState(PCB::Blocked);
			this->valueBlocked->AddNode(PCB::runningThread);
			asm sti;
			dispatch();
		}

	}
	else
		return maxTimeToWait;

	return maxTimeToWait;

}

void KernelSem::FreeOneValueBlocked(){

	PCBList::PCBNode* temp=this->GetValueBlocked()->GetHead();
	temp->myPCB->SetThreadState(PCB::Ready);
	Scheduler::put(temp->myPCB);
	this->GetValueBlocked()->MoveHeadNext();
	delete temp;
}
int KernelSem::FreeNValueBlocked(int n){

	if(this->valueBlocked->IsEmpty()==1)
		return 0;

	//NEKI IF OVDE ZA MANJE VECE
	int x;
	if(this->valueBlocked->GetItemCnt()>n)
		 x=n;
	else
		x=this->valueBlocked->GetItemCnt();

	int ret=x;

	PCBList::PCBNode* temp=this->GetValueBlocked()->GetHead();

	while(x>0 || temp!=0){
		temp->myPCB->SetThreadState(PCB::Ready);
		Scheduler::put(temp->myPCB);
		this->valueBlocked->RemoveByID(temp->myPCB->GetThreadID());
		x--;

		temp->next;
	}

	return ret;
}

int KernelSem::signal(int n) {


	if(n>0){
		asm cli;
		int ret=this->FreeNValueBlocked(n);
		this->sem_val+=ret;
		asm sti;
		return ret;
	}
	else if (n==0){

		if(this->sem_val++<0){
			asm cli;
			this->FreeOneValueBlocked();
			asm sti;
			return 1;
		}
	}
	else
		return n;

}

int KernelSem::val() {
	return this->sem_val;
}

PCBList* KernelSem::GetTimeBlocked(){
	return this->timeBlocked;
}

PCBList* KernelSem::GetValueBlocked(){
	return this->valueBlocked;
}

