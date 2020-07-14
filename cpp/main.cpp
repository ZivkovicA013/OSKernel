#include "System.h"
#include "PCB.h"
#include "Thread.h"
#include "UThreadA.h"
#include "UThreadB.h"
#include "Semap.h"
#include "KerSem.h"
#include "Event.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

int counter = 0;



void* operator new(unsigned size) {

  void* ret = malloc(size);

  if(ret==0)
    exit(1);//Out of mem
  counter++;

  return ret;
}


void operator delete(void* loc) {


  if(loc != 0){
    counter--;
    free(loc);
  }
}


extern int userMain(int argc, char** argv);

int main(int argc,char** argv){


	System* sys=new System();

	lock;
	printf("USER MAIN STARTS \n");
	unlock;

	int i,j,k;

	int x=userMain(argc,argv);

	/*for ( i = 0; i <5; i++) {
		for (j = 0; j< 10000; ++j)
			for ( k = 0; k < 30000; ++k);
	}*/


	lock;
	printf("System END! \n");
	unlock;

	sys->restore();


}
