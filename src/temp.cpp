#include "System.h"
#include "PCB.h"
#include "Thread.h"
#include "UThreadA.h"
#include "UThreadB.h"
#include "Semap.h"
#include "KerSem.h"

#include<stdio.h>
#include<stdlib.h>


int t=-1;
const int n=15;
Semaphore s(1);

class TestThread : public Thread
{
private:
	Time waitTime;

public:

	TestThread(Time WT): Thread(), waitTime(WT){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	asm cli;
	printf("Thread %d waits for %d units of time...\n",PCB::runningThread->GetThreadID(),waitTime);
	asm sti;
	int r = s.wait(waitTime);
	if(getId()%2)
		s.signal();
	asm cli;
	printf("Thread %d finished: r=%d \n",PCB::runningThread->GetThreadID(),r);
	asm sti;
}

Semaphore* mutex = 0;



void tick()
{
	t++;
	if(t){
		asm cli;
		printf("%d\n",t);
		asm sti;
	}
}


int userMain(int argc, char** argv)
{
	lock;
	printf("Test starts.\n");
	unlock;

	TestThread* t[n];
	int i;
	for(i=0;i<n;i++)
	{
		t[i] = new TestThread(5*(i+1));
		t[i]->start();
	}
	for(i=0;i<n;i++)
	{
			t[i]->waitToComplete();
	}
	delete t;
	printf("Test ends.\n");
	unlock;

	return 0;

}



