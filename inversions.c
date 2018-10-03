#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

long nextInt();
long long contali(long *v, long n);

int main(){
	long n, i;
// lettura input
	scanf("%ld", &n);
	long v[n];
	for(i=0; i<n; i++) v[i]=nextInt();
	printf("%lld\n", contali(v, n));
	/*--------------*/ //getch();
	return 0;
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

// core ricorsivo del programma

long long contali(long *v, long n){
	if (n==1) return 0;
	long long count=0, u_passati=0;
	long i=0, j=n/2, u[n];
	count=contali(v, n/2)+ contali(&v[n/2], n-n/2);
	while(i<n/2 || j<n){
		while((v[i]<=v[j] || j>=n) && i<n/2){
			u[i+j-n/2]=v[i];
			i++;
			count+=u_passati;
		}
		while((v[j]<v[i] || i>=n/2) && j<n){
			u[i+j-n/2]=v[j];
			j++;
			u_passati++;
		}
	}
	for(i=0; i<n; i++) v[i]=u[i];
	return count;
}