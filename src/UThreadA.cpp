/*
 * UThreadA.cpp
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */

#include "UThreadA.h"
#include <stdio.h>

#define lock asm cli

#define unlock asm sti

UThreadA::UThreadA(StackSize stackSize,Time timeSlice):Thread(stackSize,timeSlice) {
	// TODO Auto-generated constructor stub
}

UThreadA::~UThreadA() {
	//this->waitToComplete();
}

void UThreadA::run(){


	int i,j,k;



	for (i =0; i <10; i++) {
		lock;
		printf("u A %d ID niti je %d \n",i,this->getId());
		unlock;
			for ( k = 0; k<10000; ++k){
					for (j = 0; j <30000; ++j);
			}

		}



}
