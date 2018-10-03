#include<stdio.h>

int main(){
	long n, i;
	scanf("%ld", &n);
	long k;
	long long ctr=0, max=0;
	for(i=0; i<n; i++){
		scanf("%ld", &k);
		ctr+=k;
		if(ctr>max) max=ctr;
		if (ctr<0) ctr=0;
	}
	printf("%lld", max);
	/*----------------*/// getch();
	return 0;
}