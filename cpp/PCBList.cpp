/*
 * PCBList.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#include<stdio.h>
#include"PCBList.h"
#include "Thread.h"



PCBList::PCBList(){

	this->ListHead=0;
	this->ListTail=0;
	this->element_cnt=0;
}

void PCBList::AddNode(PCB * pcb){

	PCBNode* novi=new PCBNode(pcb);

	if(this->ListHead==0)
		this->ListHead=novi;
	else
		this->ListTail->next=novi;

	this->ListTail=novi;
	this->ListTail->next=0;
	this->element_cnt++;

}
void PCBList::PrintAll(){

	PCBNode* temp=this->ListHead;
	if(temp==0)
	{
		asm cli;
		printf("Prazno \n");
		asm sti;
		return;
	}

	while(temp!=0){

		asm cli;
		printf("ID Cvora je %d Stanje Cvora je %d \n",temp->myPCB->GetThreadID(),temp->myPCB->GetThreadState());
		asm sti;
		temp=temp->next;
	}

}
PCB* PCBList::GetByID(int id){

	PCBNode* temp=this->ListHead;

	while(temp!=0){

		if(temp->myPCB->GetThreadID()==id)
			return temp->myPCB;

		temp=temp->next;
	}

	temp=0;

	return 0;

}
int PCBList::GetItemCnt(){
	return this->element_cnt;
}
void PCBList::DeleteCurrent(){

	//Popravi uz waitToComplete
}
//Problem sa brisanjem,mora da se obrise prethodni.
void PCBList::MoveHeadNext(){
	if(this->ListHead->next!=0){
		this->ListHead=this->ListHead->next;
	}
	else
		this->ListHead=0;
}

void PCBList::RemoveByID(int id){

	//krpljenje

}
int PCBList::IsEmpty(){

	if(this->ListHead==0)
		return 1;
	else
		return 0;

}

PCBList::PCBNode* PCBList::GetHead(){
	return this->ListHead;
}

int PCBList::AllFinished(){

	return 0;
}


PCBList::~PCBList(){

	lock;

	if(this->ListHead==0)
		return;

	while(this->ListHead!=0){
		PCBNode* s=ListHead;
		ListHead=ListHead->next;
		delete s;
	}

	this->ListTail=0;
	this->ListHead=0;


	unlock;

}
