#include<stdio.h>
#include<stdlib.h>

void sort(long *v, long x, long y);
long distribuisci(long *v, long x, long p, long y);
void scambia(long *x, long *y);

int main(){
	long n, i;
	scanf("%ld", &n);
	long v[n];
	for(i=0; i<n; i++) scanf("%ld", &v[i]);
	srand(time(NULL));
	sort(v, 0, n-1);
	for(i=0; i<n; i++) printf("%ld ", v[i]);
	/*---------------------------------*/// getch();
	return 0;
}


void sort(long *v, long x, long y){
	long p;
	if (x>=y-1) {
		if (v[x]>v[y]) scambia(&v[x], &v[y]);
	}
	else{
		p=x+rand()%(y-x+1);
		p=distribuisci(v, x, p, y);
		if (p>x) sort(v, x, p-1);
		if (p<y) sort(v, p+1, y);	
	}
	
}

long distribuisci(long *v, long x, long p, long y){
	scambia(&v[p], &v[y]);
	long i=x, j=y-1;
	while(i<j){
		while(i<=j && v[i]<=v[y]) i++;
		while(i<j && v[j]>v[y]) j--;
		if (i<j)scambia(&v[i], &v[j]);
	}
	scambia(&v[i], &v[y]);
	return i;
}

void scambia (long *x, long *y){
	long temp=*x;
	*x=*y;
	*y=temp;
}