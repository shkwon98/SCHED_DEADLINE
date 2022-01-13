// Compiler flags: gcc name.c -o name -O0 -Wall -lm -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "sched_deadline.h"

void *rt_thread(void *data) {
  /* scheduler attributes */
	struct sched_attr attr;
	float period_ms = 1;

	printf("Thread ID: [%ld]\n", gettid());

	/* set up sched_attr structure */
	attr.size = sizeof(attr);
	attr.sched_policy = SCHED_DEADLINE;
	attr.sched_flags = 0;
	attr.sched_nice = 0;
	attr.sched_priority = 0;
	attr.sched_runtime = 0.95 * period_ms * 1000 * 1000;
	attr.sched_period = attr.sched_deadline = period_ms * 1000 * 1000;

	/* set sched deadline */
  	if(sched_setattr(gettid(), &attr, 0)) {
		perror("sched_setattr");
	  	exit(1);
	}

	/* loop starts */
	while (1) {
 	/* WRITE YOUR CODE BELOW */
       
		sched_yield();
	}

    	return NULL;
}


int main(int argc, char* argv[]) {

  	pthread_t thread;

  	/* Create a pthread with specified attributes */
  	pthread_create(&thread, NULL, rt_thread, NULL);
  	sleep(10);

  	/* Join the thread and wait until it is done */
  	pthread_join(thread, NULL);
  
  	printf("main dies");
  	return 0;
}
