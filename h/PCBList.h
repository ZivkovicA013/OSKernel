/*
 * PCBList.h
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#ifndef PCBLIST_H_
#define PCBLIST_H_

#include "PNode.h"


class PCBList {

private:
	PNode* ListHead;
	PNode* ListTail;

public:

	PCBList();

	void AddNode(PCB * pcb);
	void PrintAll();
	int  AllFinished();//1->yes 0->no
	void RemoveByID(int id);
	PCB* GetByID(int id);//PCB return method
	~PCBList();


};

#endif /* PCBLIST_H_ */
