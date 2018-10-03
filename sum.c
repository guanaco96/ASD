#include<stdio.h>

int main(){
	long n, i, ctr=0;
	scanf("%ld", &n);
	int k;
	for(i=0; i<n; i++) {
		scanf("%d", &k);
		ctr+=k;		
	}
	printf("%ld\n", ctr);
	return 0;
}