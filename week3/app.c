#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	int dev;
	char buffer[1024];
	int num;
	printf("Device driver test.\n");

	dev = open("/dev/sysprog_device", O_RDWR);

	printf("Input the number\n");
	if(dev == -1)
	{
		perror("failed open because ");
		return 1;
	}

	printf("dev = %d\n", dev);
	
	while(1){
		scanf("%s", buffer);
		write(dev, buffer, strlen(buffer));
		read(dev, buffer, sizeof(buffer));
		printf("read from device: %s\n", buffer);
	}
/*
	while(1){
		scanf("%d", &num);
		write(dev, &num, 4);
		read(dev, buff, 4);
		printf("buff : %s\n", buff);
	}
*/
	//write(dev, "1234", 4);
	//read(dev, buff, 4);
	//printf("read from device: %s\n", buff);
	close(dev);
	
	exit(EXIT_SUCCESS);

}
