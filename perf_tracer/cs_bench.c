#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>

typedef struct thread_arg {
        char name[16];
	cpu_set_t  cpuset;
	uint64_t rounds;
} thread_arg;

pthread_barrier_t   barrier; // the barrier synchronization object
unsigned flag = 0;
//uint32_t total_rate;
int profile_fd = -1;

pthread_mutex_t read_data_mutex = PTHREAD_MUTEX_INITIALIZER;
__thread uint64_t global_data __attribute((aligned(8))) = 0;
uint64_t inc_step =1;


static uint64_t get_time() {
	uint64_t ms;
	time_t s;

	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);

	s  = spec.tv_sec;
	ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
	if (ms > 999) {
		s++;
		ms = 0;
	}

	return ms+s*1.0e3;
}

void* read_data(void *arg) {
	int s;
	char val[1024];
	pthread_t thread;
	thread_arg *thread_arg = arg;
	cpu_set_t  *cpuset = &thread_arg->cpuset;
	uint64_t start, stop;
	unsigned enabled_flag = 0;
	unsigned disabled_flag = 1;

	thread = pthread_self();
	s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), cpuset);
	pthread_setname_np(thread, thread_arg->name);
	if (s != 0) {
		perror("Error set thread  affinity");
		return NULL;
	}

	/*
	  wait all worker thread reach same point
	  and the manager thread should enable
	  function_profile already
	 */
	pthread_barrier_wait(&barrier);
	start = get_time();

	for (int i = 0; i < thread_arg->rounds; ++i)
	{
		pthread_mutex_lock(&read_data_mutex);
		//__atomic_fetch_add(&global_data, 1, __ATOMIC_SEQ_CST);
		++global_data;
		//__atomic_store_n(&global_data, 1, __ATOMIC_SEQ_CST);

		//global_data += inc_step;
		pthread_mutex_unlock(&read_data_mutex);
	}

	if(__atomic_compare_exchange(&flag, &enabled_flag, &disabled_flag, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
	  printf("trigger another exit\n");

	stop = get_time();

	printf("do read io in %.3f second, cal %lu\n", (stop-start)/1.0e3, global_data);
	//total_rate += rate;
	// Un-mmaping doesn't close the file, so we still need to do that.
	return (void*)global_data;
}

int main(int argc, const char *argv[])
{
	uint8_t cpu_num = 0;
	char* cpu_list;
	uint64_t final_result = 0;

	const char *debugfs = "/sys/kernel/debug";
	char path[256];

	thread_arg *args;
	pthread_t *threads;


	if(argc == 1)
		cpu_num = 1;
	else if(argc == 3) {
		cpu_num = atoi(argv[1]);
		cpu_list = malloc(strlen(argv[2]));
		strcpy(cpu_list, argv[2]);
	}

	args = malloc(sizeof(thread_arg)*cpu_num);
	threads = malloc(sizeof(pthread_t)*cpu_num);

	for(int i = 0; i < cpu_num; ++i) {
		char *ptr;
		if( i != cpu_num -1) {
			ptr = strchr(cpu_list, ',');
			*ptr ='\0';
		}

		CPU_ZERO(&args[i].cpuset);
		CPU_SET(atoi(cpu_list), &args[i].cpuset);
		args[i].rounds = 1000*1000*100;

		if( i != cpu_num -1)
			cpu_list = ptr+1;
	}

	pthread_barrier_init(&barrier, NULL, cpu_num+1);

	for(int i = 0; i < cpu_num; ++i) {
		pthread_create(&threads[i], NULL, read_data, (void*)&args[i]);
	}


	/* ensure all worker thread start at same time */
	pthread_barrier_wait(&barrier);

	/* enable function_profile*/
	//write(profile_fd, "1", 1);

	for(int i = 0; i < cpu_num; ++i) {
		void *status;
		pthread_join(threads[i], &status);
		final_result += (uint64_t)status;
	}

	printf("final cal result %lu\n", final_result);
 err:
	close(profile_fd);
	return 0;
}
