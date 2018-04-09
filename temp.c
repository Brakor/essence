#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

float getOldTotal(char* filename){
	if(filename == NULL){
		return -1;
	}
	
	int fd = open(filename, O_RDONLY, 0444);
	int rbytes = 1;
	float total;
	float* buf;
	
	if(fd == -1){
		perror("Problème open");
		return -1;
	}
	
	buf = malloc(sizeof(total));
	memset(&buf, 0x0, sizeof(total));
	
	while(1){
		rbytes = read(fd, &buf, sizeof(total));
		
		if(rbytes == -1){
			perror("Problème read");
			return -1;
		}
		
		if(rbytes == 0){
			break;
		}
		
		total += (float) *buf;
		
		memset(&buf, 0x0, sizeof(total));
	}
	
	return total;
}

void save(float new){
	int fd = open("essence.dat", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	
	if(fd == -1){
		perror("Couldn't open output file");
		exit(-1);
	}
	
	write(fd, &new, sizeof(new));
}
	
int main(void){
	float temp = 0, fval = 0;
	char answ = '\0';
	
	printf("New submit ? y/n\n");
	scanf("%f", &answ);
	
	if(answ == 'y'){
		printf("How many did you spend ?\n");
		read(0, &temp, sizeof(temp));
		
		fval = getOldTotal("essence.dat") + temp;
		
		save(fval);
	} else if(answ == 'n'){
		printf("You spent %.2f this month\n", getOldTotal("essence.dat"));
	}

	return EXIT_SUCCESS;
}