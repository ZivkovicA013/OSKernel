/*
 * PCBNode.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#include"PNode.H"

#include<stdio.h>

PNode::PNode(PCB* pcb){

	this->pcb=pcb;
	this->next=0;
}

void PNode::PrintMe(){
	printf("Moj ID je %d \n",this->pcb->GetThreadID());
}

void PNode::SetNext(PNode* node){
	this->next=node;
}

PCB* PNode::GetPCB(){
	return this->pcb;
}

PNode* PNode::GetNext(){
	return this->next;
}
void PNode::SetPCBNull(){
	this->pcb=0;
}
void PNode::SetNextNull(){
	this->next=0;
}
