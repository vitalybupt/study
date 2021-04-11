#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int trace_fd = -1;
int marker_fd = -1;

#define STARTTRACE(MSG) ({ int len = strlen(MSG); write(trace_fd, "1", 1); write(marker_fd, "====TRACE sleep START HERE====\n", 31); })
#define STOPTRACE(MSG) ({ int len = strlen(MSG); write(marker_fd, "====TRACE sleep STOP HERE====\n", 30); write(trace_fd, "0", 1);})

int main() {
	const char *debugfs = "/sys/kernel/debug";
	char path[256];
	struct timespec req;

	/* open trace_fd */
	strcpy(path, debugfs);
	strcat(path, "/tracing/tracing_on");
	if((trace_fd = open(path, O_WRONLY)) <= 0)
		goto err;

	/* open trace_marker fd */
	strcpy(path, debugfs);
	strcat(path, "/tracing/trace_marker");

	if((marker_fd = open(path, O_WRONLY)) <= 0)
		goto err;

	req.tv_sec = 0;
	req.tv_nsec = 1000;
	STARTTRACE("sleep");
	nanosleep(&req, NULL);
	STOPTRACE("sleep");

	return 0;

err:
	if(marker_fd >= 0)
		close(marker_fd);
	if(trace_fd >= 0)
		close(trace_fd);
	return -1;
}
