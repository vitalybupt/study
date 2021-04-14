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

#include <pthread.h>
#include <sched.h>
#include <math.h>

typedef struct thread_arg {
        char filepath[32];
        char name[16];
	cpu_set_t  cpuset;
} thread_arg;

pthread_barrier_t   barrier; // the barrier synchronization object
unsigned flag = 0;
uint32_t total_rate;
int profile_fd = -1;

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
	const char *filepath = thread_arg->filepath;
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

	int fd = open((char*)filepath, O_RDONLY, (mode_t)0600);

	if (fd == -1)
	{
		perror("Error opening file for reading");
		perror(filepath);
		return NULL;
	}

	struct stat fileInfo = {0};

	if (fstat(fd, &fileInfo) == -1)
	{
		perror("Error getting the file size");
		return NULL;
	}

	if (fileInfo.st_size == 0)
	{
		fprintf(stderr, "Error: File is empty, nothing to do\n");
		return NULL;
	}


	char *map = mmap(0, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED)
	{
		close(fd);
		perror("Error mmapping the file");
		return NULL;
	}

	/*
	  wait all worker thread reach same point
	  and the manager thread should enable
	  function_profile already
	 */
	pthread_barrier_wait(&barrier);
	start = get_time();

	off_t i;
	for (i = 0; i < fileInfo.st_size; i+=1024)
	{
	  memcpy(val, &map[i], 1024);
	  if(flag == 1) {
	    break;
	  }
	}

	if(__atomic_compare_exchange(&flag, &enabled_flag, &disabled_flag, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
	  printf("trigger another exit\n");
	
	stop = get_time();
	// Don't forget to free the mmapped memory
	if (munmap(map, fileInfo.st_size) == -1)
	{
		close(fd);
		perror("Error un-mmapping the file");
		return NULL;
	}

	uint32_t rate = (int)round(i/((stop-start)*1.0e3));
	printf("do read io in %.3f second, rate %d MBytes/second\n", (stop-start)/1.0e3, rate);
	total_rate += rate;
	// Un-mmaping doesn't close the file, so we still need to do that.
	close(fd);
	return NULL;
}

int main(int argc, const char *argv[])
{
	uint8_t cpu_num = 0;
	char* cpu_list;

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
		sprintf(args[i].filepath, "/home/zjw/tmp/mmapped%d.bin", i+1);
		sprintf(args[i].name, "f_profile%d", i);
		if( i != cpu_num -1) {
			ptr = strchr(cpu_list, ',');
			*ptr ='\0';
		}

		CPU_ZERO(&args[i].cpuset);
		CPU_SET(atoi(cpu_list), &args[i].cpuset);
		if( i != cpu_num -1)
			cpu_list = ptr+1;
	}

	/* open _fd */
	strcpy(path, debugfs);
	strcat(path, "/tracing/function_profile_enabled");
	if((profile_fd = open(path, O_WRONLY)) <= 0) {
		perror("Error open function_profile_enabled file");
		goto err;
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
		pthread_join(threads[i], NULL);
	}

	printf("total rate %u MBytes/second\n", total_rate);
 err:
	close(profile_fd);
	return 0;
}
