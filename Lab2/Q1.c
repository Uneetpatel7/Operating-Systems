#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char *argv[]){

	if(argc!=2)
    {
        fprintf(stderr,"Not a valid input\n");
        exit(0);
    }

    int k = atoi(argv[1]);

    if(k<=0)
    {
        fprintf(stderr,"Enter the positive number\n");
        exit(0);
    }

	pid_t pr_id;

	pr_id = fork();

	if(pr_id==0){
	printf("The output sequence of the child process is:\n" );
	printf("%d\n",k);	
	while (k!=1){
			
		if (k%2 == 0){
			k = k/2;
		}

		else if (k%2 == 1){
		k = 3 *k+1;
		}

		printf("%d\n",k);
		}

	exit(0);
	}

	else{
		wait(NULL);
	}
return 0;
}
