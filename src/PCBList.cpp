/*
 * PCBList.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#include"PCBList.h"
#include<stdio.h>


PCBList::PCBList(){

	this->ListHead=0;
	this->ListTail=0;
}

void PCBList::AddNode(PCB * pcb){

	PNode * new_node=new PNode(pcb);

	if(this->ListHead==0)
		this->ListHead=new_node;
	else
		this->ListTail->SetNext(new_node);
	this->ListTail=new_node;

}
void PCBList::PrintAll(){

	PNode* temp=this->ListHead;

	while(temp!=0){

		temp->PrintMe();
		temp=temp->GetNext();
	}

}
PCB* PCBList::GetByID(int id){

	PNode* temp=this->ListHead;

	while(temp!=0){

		if(temp->GetPCB()->GetThreadID()==id)
			return temp->GetPCB();

		temp=temp->GetNext();
	}

}

void PCBList::RemoveByID(int id){

	PNode* front=this->ListHead;
	PNode* back=front;

	while(front->GetPCB()->GetThreadID()!=id){
			back=front;
			front=front->GetNext();
	}

	if(back==front) //u prvom je trazeni id
	{
		ListHead->SetPCBNull();
		ListHead=ListHead->GetNext();
		front->SetNextNull();
	}
	else
	{
		back->SetNextNull();
		back->SetNext(front->GetNext());
		front->SetNextNull();
	}


}

int PCBList::AllFinished(){

	asm cli;

	PNode* temp=this->ListHead;

		while(temp!=0){

			if(temp->GetPCB()->GetThreadState()!=PCB::Finished)
					return 0;


			temp=temp->GetNext();
		}

		asm sti;

		return 1;
}
