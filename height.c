#include<stdio.h>
#define max(a,b) a>b ? a : b

struct elenco{
	long id;
	long sx;
	long dx;
};


long contali(struct elenco *v, long k);

int main(){
	long n, r, i;
	
	scanf("%ld %ld", &n, &r);
	struct elenco v[n];
	for(i=0; i<n; i++) scanf("%ld %ld %ld", &(v[i].id), &(v[i].sx), &(v[i].dx));
		
	printf("%ld\n", contali(v, r));
	return 0;
}

long contali(struct elenco *v, long k){
	long x=0, y=0;
	if(v[k].sx!=-1)x=1+contali(v, v[k].sx);
	if(v[k].dx!=-1) y=1+contali(v, v[k].dx);
	
	return max(x,y);

}


