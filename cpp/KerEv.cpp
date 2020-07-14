/*
 * KerEv.cpp
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#include "KerEv.h"
#include<stdio.h>
KernelEv::KernelEv(IVTNo intnum) {
	// TODO Auto-generated constructor stub
	this->myBoss=PCB::runningThread->GetThreadID();
	this->val=1;
	this->blocked=0;
	this->ivtn=intnum;
	this->myBossPCB=PCB::runningThread;
}

KernelEv::~KernelEv() {
	// TODO Auto-generated destructor stub
}

void KernelEv::wait() {

	asm cli;

	if(myBoss!=PCB::runningThread->GetThreadID()){
		asm sti;
		return;
	}

	 if(val==0){
		 PCB::runningThread->SetThreadState(PCB::Blocked);
		 this->blocked=1;
		 asm sti;
		 dispatch();
	 }
	 else{
		 val=0;
		 asm sti;
		 return;
	 }

}

void KernelEv::signal() {
//blocked pokazivac!
	asm cli;

	if(this->blocked==0){
		this->val=1;
		asm sti;
		return;
	}

	if(this->blocked!=0){
		this->myBossPCB->SetThreadState(PCB::Ready);
		Scheduler::put(this->myBossPCB);
		this->blocked=0;
		asm sti;
	}

}
