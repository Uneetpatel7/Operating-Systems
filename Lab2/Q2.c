#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main(){

	char I[100];
	char inbuf[100];
	printf("Input The String: ");
	fgets(I,100,stdin);
	int pipe1[2];
	int pipe2[2];

	if(pipe(pipe1)<0  || pipe(pipe2)<0){
		fprintf(stderr,"Piping Failed\n");
    	return 0;
    }

	pid_t pid;

	pid = fork();

	if(pid>0){
		write(pipe1[1], I, strlen(I)+1);
		close(pipe1[1]);

		wait(NULL);
		char outbuf[100];	
		read(pipe2[0], outbuf, strlen(I)+1);
		printf("The String Created by the process is: ");
		printf("%s\n", outbuf);
		close(pipe2[0]);

	}

	else if (pid==0){
		read(pipe1[0], inbuf, strlen(I)+1);
		char outbuf[100];
		int i=0;
		while(inbuf[i]!='\0'){
			if(inbuf[i]==' '){
                outbuf[i]=' ';
			}
			else if(inbuf[i]<='Z'){
				outbuf[i] = inbuf[i] - 'A' + 'a';
			}
			else if(inbuf[i]<='z'){
				outbuf[i] = inbuf[i] - 'a' + 'A';
			}
		i++;
		}
		outbuf[i-1] = '\0';
		close(pipe1[0]);

		write(pipe2[1], outbuf, strlen(outbuf)+1);
		close(pipe2[1]);
		exit(1);
	}

	return 0;
}
