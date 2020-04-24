/*
 * PCBList.h
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#ifndef PCBLIST_H_
#define PCBLIST_H_

#include "PCB.h"


class PCBList {

private:

	struct PCBNode{

		PCB* myPCB;
		PCBNode* next;
		int deleted;//1 da 0 ne

		PCBNode(PCB* pcb,PCBNode* n=0):myPCB(pcb),next(n),deleted(0){}

		~PCBNode(){delete this->myPCB;}
	};

	PCBNode* ListHead;
	PCBNode* ListTail;

public:

	PCBList();

	void AddNode(PCB * pcb);
	void PrintAll();
	void DeleteCurrent();
	void RemoveByID(int id);

	int  AllFinished();//1->yes 0->no
	int IsEmpty();//1->yes,0->no

	PCB* GetByID(int id);//PCB return method
	PCBNode* GetHead();

	~PCBList();

};

#endif /* PCBLIST_H_ */
