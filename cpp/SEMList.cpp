/*
 * SEMList.cpp
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#include "SEMList.h"
#include <stdio.h>

SEMList::SEMList() {
	// TODO Auto-generated constructor stub
	this->ListHead=0;
	this->ListTail=0;
}

void SEMList::AddNode(Semaphore* s) {


	SEMNode* novi=new SEMNode(s);

	if(this->ListHead==0)
		this->ListHead=novi;
	else
		this->ListTail->next=novi;

	this->ListTail=novi;
	this->ListTail->next=0;
}

SEMList::SEMNode* SEMList::GetHead() {
	if(this->ListHead==0)
		return 0;
	else
		return this->ListHead;
}

int SEMList::IsEmpty() {
	if(this->ListHead==0)
		return 1;
	else
		return 0;
}

void SEMList::PrintAll(){


	SEMList::SEMNode* temp=this->ListHead;

	while(temp!=0){
		printf("SEM ID %d \n",temp->mySEM->GetMyImpl()->GetMyId());
		temp=temp->next;
	}

}

SEMList::~SEMList() {

	asm cli;

	if(this->ListHead==0)
		return;

	while(this->ListHead!=0){
		SEMNode* s=ListHead;
		ListHead=ListHead->next;
		delete s;
	}

	this->ListTail=0;
	this->ListHead=0;

	asm sti;

}

