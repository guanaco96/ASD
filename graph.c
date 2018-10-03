#include<stdio.h>
#include<stdlib.h>

struct nodo{
	long label;
	struct list *entranti;
};

struct list{
	long label;
	struct list *fw;
	struct list *bw;
};

struct list * aggiungi(struct list * l, long x);


int main(){
	long n, m, i, from, to;
	struct nodo *vert;
	struct list *p;
	
	scanf("%ld %ld", &n, &m);
	vert= (struct nodo*) malloc (sizeof(struct nodo)*n);
	for(i=0; i<n; i++){
		vert[i].label=i;
		vert[i].entranti=NULL;
	}
	for(i=0; i<m; i++){
		scanf("%ld %ld", &from, &to);
		vert[to].entranti=aggiungi(vert[to].entranti, from);
	}
	for(i=0; i<n; i++){
		p=vert[i].entranti;
		while(p!=NULL){
			printf("%ld ", p->label);
			p=p->fw;
		}
		printf("\n");
	}

	return 0;
}


struct list * aggiungi(struct list * l, long x){
	struct list *p, *q;
	p=(struct list*)malloc(sizeof(struct list));
	p->label=x;
	if(l==NULL){
		p->fw=NULL;
		return p;
	}
	if(x<=l->label){
		p->fw=l;
		return p;
	}
	else{
		l->fw=aggiungi(l->fw, x);
		return l;
	}
}

