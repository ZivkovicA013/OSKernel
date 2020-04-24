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
}

void PCBList::AddNode(PCB * pcb){

	PCBNode* novi=new PCBNode(pcb);

	if(this->ListHead==0)
		this->ListHead=novi;
	else
		this->ListTail->next=novi;

	this->ListTail=novi;
	this->ListTail->next=0;

}
void PCBList::PrintAll(){

	PCBNode* temp=this->ListHead;

	while(temp!=0){

		printf("ID Cvora je %d Stanje Cvora je %d \n",temp->myPCB->GetThreadID(),temp->myPCB->GetThreadState());
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
void PCBList::DeleteCurrent(){

	//Popravi uz waitToComplete
}

void PCBList::RemoveByID(int id){



  if(id==0 || id==1 || this->ListHead==0)
	  return;

  if(this->ListHead->myPCB->GetThreadID()==id){
	  //U prvom je ID
	  PCBNode* temp=this->ListHead;
	  this->ListHead=this->ListHead->next;
	  temp->deleted=1;
	  return;
  }


  if(this->ListTail->myPCB->GetThreadID()==id){
	  //u poslednjem je ID
	  PCBNode* temp=this->ListHead;

	  while(temp->next!=this->ListTail)
		  temp=temp->next;

	  this->ListTail=temp;
	  this->ListTail->next=0;
	  temp->next->deleted=1;
	  return;
  }

  PCBNode* curr=this->ListHead;
  PCBNode*back=curr;



  while(curr!=0){

	  if(curr->myPCB->GetThreadID()==id){
		   back->next=curr->next;
		   curr->next=0;
		   curr->deleted=1;
		   return;
	  }

	  back=curr;
	  curr=curr->next;
  }

//brisanje tail-a






}
int PCBList::IsEmpty(){

	PCBNode* temp=this->ListHead;

	while(temp!=0){
		if(temp->deleted==0)
			return 0;
		temp=temp->next;
	}

	return 1;

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
