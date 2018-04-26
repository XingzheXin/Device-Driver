#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("Usage -- [1 - BLACK | 2 - WHITE] [<int> - Number of items to produce]");
		exit(1);
	}
	
	char outstr[32] = {};

	int n = atoi(argv[2]);

	if (n <= 0) {
		printf("Number of items not valid");
		exit(1);
	}

	int fp;	
	fp = open("/dev/scullbuffer0", O_WRONLY);

	if(fp == -1) {
		perror("Errno indicates: ");
		exit(1);
	}
	
	printf("%d\n", n);
	printf("%s\n", argv[1]);

	for(int i = 0; i < n; i++) {
		if (!strcmp(argv[1], "1")) {
			snprintf(outstr, 32, "BLACK%05d", i+1);
			printf(outstr);
			printf("\n");
		}	
		else if (!strcmp(argv[1], "2")) {
			snprintf(outstr, 32, "WHITE%05d", i+1);
			printf(outstr);
			printf("\n");
		}	
		write(fp, outstr, sizeof(outstr));
	}

	close(fp);
	return 0;
}
