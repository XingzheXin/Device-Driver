#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc != 2) {
		printf("Usage -- [<int> - Number of items to consume]");
		exit(1);
	}
	
	char instr[32] = {};

	int n = atoi(argv[1]);

	if (n <= 0) {
		printf("Number of items not valid");
		exit(1);
	}

	int fp;	
	fp = open("/dev/scullbuffer0", O_RDONLY);

	if(fp == -1) {
		perror("Errno indicates: ");
		exit(1);
	}

	for(int i = 0; i < n; i++) {
		read(fp, instr, 32);
		printf(instr);
		printf("\n");
	}

	close(fp);
	return 0;
}
