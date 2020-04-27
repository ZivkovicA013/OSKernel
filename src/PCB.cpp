/*
 * PCB.cpp
 *
 *  Created on: Apr 7, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include "System.h"
#include"SCHEDULE.H"
#include <dos.h>
#include <stdio.h>

#define lock asm cli
#define unlock asm sti


PCB * PCB::mainThread=0;
PCB * PCB::idleThread=0;
PCB * PCB::runningThread;

PCB::PCB(unsigned long size,ID id,Time time) {



	lock;

   this->ThreadID=id;
   this->TimeSlice=time;
   this->Stack_Size=size;
   this->ThreadState=New;
   this->PCBWaitingList=new PCBList();
   this->TimeToWait=0;

   this->myStack=new unsigned[size];

#ifndef BCC_BLOCK_IGNORE
   this->myStack[size-1]=0x200;//PSW
   this->myStack[size-2]=FP_SEG(PCB::WrapperFunction);
   this->myStack[size-3]=FP_OFF(PCB::WrapperFunction);

   this->Stack_SEG=FP_SEG(this->myStack+size-12);
   this->Stack_OFF=FP_OFF(this->myStack+size-12);
   this->BasePointer=FP_OFF(this->myStack+size-12);


#endif



   unlock;

}

PCB::PCB(){
//konstruktor za main
	this->myStack=0;
	this->Stack_Size=0;
	this->TimeSlice=1;
	this->ThreadID=0;
	this->myThread=0;
	this->TimeToWait=0;
	this->PCBWaitingList=new PCBList();
	this->ThreadState=PCB::Running;
}
ID PCB::GetThreadID(){
	return (int)this->ThreadID;
}
void PCB::SetThreadState(State s){
	this->ThreadState=s;
}

PCB::State PCB::GetThreadState(){

	return this->ThreadState;
}

int PCB::GetTimeToWait(){
	return this->TimeToWait;
}
void PCB::SetTimeToWait(int newT){
	this->TimeToWait=newT;
}


PCB::~PCB() {

	 if(myStack!=0){
		delete[] this->myStack;
		this->myStack=0;
	}
	delete this->PCBWaitingList;



}

void PCB::ReleaseAllPCB(){

		if(PCB::runningThread->PCBWaitingList->IsEmpty()==1)
			return;

		PCBList::PCBNode * temp=PCB::runningThread->PCBWaitingList->GetHead();

		while(temp!=0){

			temp->myPCB->SetThreadState(PCB::Ready);
			Scheduler::put(temp->myPCB);
			PCB::runningThread->PCBWaitingList->RemoveByID(temp->myPCB->GetThreadID());

			temp=temp->next;
		}



		return;
}

void PCB::WrapperFunction(){

	PCB::runningThread->myThread->run();
	lock;
	PCB::runningThread->SetThreadState(PCB::Finished);
	PCB::runningThread->ReleaseAllPCB();
	//System::List->RemoveByID();DOVRSI OVO!!!!!!
	unlock;
	dispatch();

}

volatile int tsp;
volatile int tss;
volatile int tbp;
volatile int cntr=1;//toliko ce main da ceka


extern void tick();

void interrupt PCB::timer(...){


	if(Thread::CS_req==0){
			cntr--;
			tick();
	}


	//KOD ZA TICM TIMERA KOD SEMAFORA


	SEMList::SEMNode* temp_s=System::Sem_List->GetHead();
	while(temp_s!=0){

		PCBList::PCBNode* temp_t=temp_s->mySEM->GetMyImpl()->GetTimeBlocked()->GetHead();
		while(temp_t!=0){
			if(temp_t->myPCB->GetTimeToWait()>0){
				int new_time=temp_t->myPCB->GetTimeToWait();
				new_time--;
				temp_t->myPCB->SetTimeToWait(new_time);
				if(new_time==0){
					temp_t->myPCB->SetThreadState(PCB::Ready);
					Scheduler::put(temp_t->myPCB);
					temp_s->mySEM->GetMyImpl()->GetTimeBlocked()->RemoveByID(temp_t->myPCB->GetThreadID());
				}
			}
			temp_t=temp_t->next;
		}
		temp_s=temp_s->next;
	}

	//KOD ZA TICK TIMERA KOD SEMAFORA


	if((cntr==0) || (Thread::CS_req==1)){

		asm{
			mov tsp,sp
			mov tss,ss
			mov tbp,bp
		}

		PCB::runningThread->Stack_OFF=tsp;
		PCB::runningThread->Stack_SEG=tss;
		PCB::runningThread->BasePointer=tbp;


		if(PCB::runningThread->ThreadState == PCB::Running){
			PCB::runningThread->ThreadState=PCB::Ready;
			if(PCB::runningThread->ThreadID!=1){
				Scheduler::put(PCB::runningThread);
			}
		}


		PCB::runningThread=Scheduler::get();

		if(PCB::runningThread==0)
			PCB::runningThread=PCB::idleThread;


		PCB::runningThread->ThreadState=PCB::Running;

		cntr=PCB::runningThread->TimeSlice;
		tsp=PCB::runningThread->Stack_OFF;
		tss=PCB::runningThread->Stack_SEG;
		tbp=PCB::runningThread->BasePointer;


		asm{
			mov sp,tsp
			mov ss,tss
			mov bp,tbp
		}


	}

	if(Thread::CS_req==0)
		asm int 60h

	Thread::CS_req=0;
}


