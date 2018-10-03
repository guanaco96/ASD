#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

long nextInt();
long trova(long , long , long *);
void scambia (long , long , long *);

int main(){
	long n, k, i, s;
// lettura input
	s=scanf("%ld %ld", &n, &k);
	long v[n];
	for(i=0; i<n; i++) v[i]=nextInt();
	printf("%ld\n", trova(n,k,v));
	return 0;
}

// core del programma, funzione ricorsiva che mi trova il k-esimio (quicksort-like)

long trova(long n, long k, long *v){
	long j=0, u[n-1], a, b, *c;
	srand(time(NULL));
	long i, r=rand()%n;
	scambia(r, n-1, v);
	for(i=0; i<n-1; i++){
		if(v[i]<v[n-1]) u[j++]=v[i];
		else u[n-2-i+j]=v[i];
	}
	
	if (j>=k+1){
		a=j,
		b=k;
		c=u;
	}
		else {
			if (j<k){
				a=n-j-1;
				b=k-j-1;
				c=&u[j];
			}
			else return v[n-1];
		}			
	return trova(a,b,c); //questo dovrebbe essere uno SWAG tail recursive*/
	
	/*
	if (j>=k+1) return trova(j, k, u);
	else	if (j==k) return v[n-1];
		else return trova(n-j-1, k-j-1, &u[j]);
	*/
	
}

void scambia (long i, long j, long *v){
	long temp;
	temp=v[i];
	v[i]=v[j];
	v[j]=temp;
}

//funzione per leggere l'input velocemente

long nextInt() {
	long n = 0;
	bool negative = false;
	int c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
		if (c == '-') {
		negative = true;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		n = 10 * n + c - '0';
		c = getchar();
	}
	return negative ? -n : n;
}
