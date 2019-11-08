#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <pthread.h>

#define MAX 122
#define MIN 48

char gesucht[64];
char fertig = 0;
int anz_threads;
char diff = MAX - MIN;

void check(unsigned char *feld,int i,int beginn, int ende){
	if(i != 0){
		feld[i] = beginn;
		feld[i-1] = feld[i-1] + 1;
		if(feld[i-1] == ende+1){
			check(feld,i-1,beginn,ende);
		}
	}
}

void *BruteForce(void *threadid){
	unsigned char string[8];
	char tmp[64];
	char hex[64];
	long tid;
	tid = (long) threadid;
	int ende = MAX;
	int beginn = MIN;
	if(tid==0){
		beginn = 0 + MIN;
	}
	unsigned char result[MD5_DIGEST_LENGTH];
	int x=beginn;
	for(int i=0;i<8;i++){
		string[i]=diff % anz_threads + tid * (diff /anz_threads) + MIN;
	}
	//string[8]='\0';
	unsigned char z;
	int test = 0;
	while(test != 32 && fertig == 0){
		test = 0;
		hex[0]='\0';
		if(x!=ende+1){
			z = string[7];
			z++;
			string[7] = z;
			//string[8] = '\0';
		}else{
			x = beginn;
			check(string,7,beginn,ende);
			//string[8]='\0';
		}

		MD5(string, strlen(string), result);
  		for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
			sprintf(tmp,"%02x",result[i]);
			strcat(hex,tmp);
		}
		if(tid == 0){
			printf("%s\t%c%c%c%c%c%c%c%c\t%d\t%d\t%d\n",hex,string[0],string[1],string[2],string[3],string[4],string[5],string[6],string[7],beginn,ende,x);
		}
		for(int i = 0; i < 32;i++){
			if(hex[i]==gesucht[i]){
				test = test+1;
			}
		}
		if(test == 32){
			fertig = 1;
			printf("\nGefunden:\t%s\t",hex);
			for(int i=0;i<8;i++){
				printf("%c",string[i]);
			}
			printf("\n");
			break;
		}
		x++;
	}
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
	if(argc == 3){
		strcpy(gesucht,argv[1]);
		anz_threads = atoi(argv[2]);
	}else{
		printf("Eingabe md5 String:\n");
		fgets(gesucht, 64, stdin);
		printf("Eingabe der Anzahl der Threads:\n");
		scanf("%d",&anz_threads);
	}
	pthread_t threads[anz_threads];
	int t;
	for(long i = 0; i < anz_threads; i++){
		t = pthread_create(&threads[i], NULL, BruteForce, (void *)i);
		if(t){
			printf("Fehler: Rückgabewert ist: %d\n",t);
		}
	}
	pthread_exit(NULL);
	return 0;
}
