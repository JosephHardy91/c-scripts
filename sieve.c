#include <stdio.h>
#include <math.h>

#define SIEVESIZE 2000000

//print sum(i for i in xrange(2, len(sieve)) if sieve[i])

double sum(double numarray[]){
	
	int arraysize=sizeof(numarray)/sizeof(int);
	int i = 0;
	double sumval = 0;
	while(i<arraysize){
		sumval+=numarray[i];
		i++;
	};
	
	return sumval;
}

int main(int argc, char *argv[]){
	printf("Got here0");
	int i;
	int sieve[SIEVESIZE];
	for(i=0;i<SIEVESIZE;i++){
		sieve[i]=1;
	};
	printf("Got here1");
	// Sieve is faster for 2M primes
	i=0;
	for(i = 2;i<floor(sqrt(sizeof(sieve)/sizeof(int)));i++){
		if(sieve[i]==1){
			int j;
			for(j=i+i; j < sizeof(sieve)/sizeof(int); j=j+i){
				sieve[j] = 0;
			};
		};
	};
	printf("Got here2");
	i=0;
	double result_sieve[SIEVESIZE];
	for(i = 2;i<floor(sqrt(sizeof(sieve)/sizeof(int)));i++){
		if(sieve[i]==1){
			result_sieve[i]=i;
		}
		else{
			result_sieve[i]=0;
		};
	};
	printf("Got here3");
	double sumval=sum(result_sieve);
	printf("%f",sumval);
	return 0;
}