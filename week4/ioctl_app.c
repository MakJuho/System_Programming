#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IOCTL_MAGIC_NUMBER 'j'

#define IOCTL_CMD_SUM	_IOWR( IOCTL_MAGIC_NUMBER, 0, int)
#define IOCTL_CMD_READ	_IOR( IOCTL_MAGIC_NUMBER, 1, int)
#define IOCTL_CMD_WRITE	_IOW( IOCTL_MAGIC_NUMBER, 2, int)

int main() {
	int fd, num=0;

	fd=open("/dev/ioctl_dev", O_RDWR);
	if(fd < 0){
		perror("Failed to open the device...");
	}

	while(1){
		scanf("%d", &num);
		ioctl(fd, IOCTL_CMD_SUM, &num);
		printf("Result from Kernel: %d\n", num);
	}

	close(fd);
	return 0;
}
