/*
 * temp.cpp
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */
#include "System.h"
#include "PCB.h"
#include "Thread.h"
#include "UThreadA.h"
#include "UThreadB.h"
#include <stdio.h>
#include <dos.h>

#define lock asm cli
#define unlock asm sti


int main(){


	lock;

	System* sys=new System();

	sys->init();
	sys->MakeMainThread();
	sys->MakeThreadList();


	//USER MAIN
	UThreadA * a  = new UThreadA(4096,2);
	UThreadB * b = new UThreadB(4096,1);
	UThreadA * c = new UThreadA(4096,1);
	UThreadB * d = new UThreadB(4096,2);
	UThreadA * e = new UThreadA(4096,2);
	UThreadB * f = new UThreadB(4096,1);
	UThreadA * g = new UThreadA(4096,1);
	UThreadB * h = new UThreadB(4096,2);
	UThreadA * aa  = new UThreadA(4096,2);
	UThreadB * bb = new UThreadB(4096,1);
	UThreadA * cc= new UThreadA(4096,1);
	UThreadB * dd = new UThreadB(4096,2);
	UThreadA * ee = new UThreadA(4096,2);
	UThreadB * ff = new UThreadB(4096,1);
	UThreadA * gg = new UThreadA(4096,1);
	UThreadB * hh = new UThreadB(4096,2);



	a->start();
	b->start();
	c->start();
	d->start();
	e->start();
	f->start();
	g->start();
	h->start();
	aa->start();
	bb->start();
	cc->start();
	dd->start();
	ee->start();
	ff->start();
	gg->start();
	hh->start();



	unlock;

	int i,j,k;


		for ( i = 0; i < 30; ++i) {
			 lock;
			 printf("U main sam \n");
			 unlock;

			for (j = 0; j< 30000; ++j)
				for ( k = 0; k < 30000; ++k);
		}
		printf("Kraj \n");



	//USER MAIN




	sys->restore();
}
