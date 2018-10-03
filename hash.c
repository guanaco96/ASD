#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define TABDIM 10000


struct opera{
	char tipo;
	long numero;
};

struct list{
	long dato;
	struct list *fw;
	struct list *bw;
};

long hash (long k);
int ricerca(struct list *v, long x);
struct list *inserisci(struct list *v, long x);
struct list *delete(struct list *v, long x);

int main(){
	long o, i;
	struct opera *w;
	struct list *v[TABDIM];
	
	for(i=0; i<TABDIM; i++) v[i]=NULL;
	scanf("%ld", &o);
	w=(struct opera *) malloc (sizeof(struct opera)*o);
	for(i=0; i<o; i++){
		while((w[i].tipo=getchar())=='\n');
		scanf("%ld", &w[i].numero);
	}
	for (i=0; i<o; i++) {
		//printf("tipo = %c \t dato= %ld\n", w[i].tipo, w[i].numero);
		if(w[i].tipo=='f') printf("%d\n", ricerca(v[hash(w[i].numero)], w[i].numero));
		if(w[i].tipo=='i') v[hash(w[i].numero)]=inserisci(v[hash(w[i].numero)], w[i].numero);
		if(w[i].tipo=='d') v[hash(w[i].numero)]=delete(v[hash(w[i].numero)], w[i].numero);
	
	}

	return 0;
}

long hash (long k){
	if(k<0) k=-k;
	return k%TABDIM;
}

int ricerca(struct list *v, long x){
	//printf("ricerco\n");
	if(v==NULL) return 0;
	else{
		if(v->dato==x) return 1;
		else return ricerca(v->fw, x);
	}
}

struct list * nuovalista(long x, struct list *back){
	//printf("nuovolisto\n");
	struct list *p;
	p=(struct list *) malloc (sizeof(struct list));
	p->dato=x;
	p->fw=NULL;
	p->bw=back;
	
	return p;
}

struct list * inserisci(struct list *v, long x){
	//printf("inserisco\n");
	struct list *p=v;
	if(v==NULL)return nuovalista(x, NULL);
	else{
		while(p->dato!=x && p->fw!=NULL) p=p->fw;
		if(p->dato!=x) p->fw=nuovalista(x, p);
		
		return v;
	}		
}

struct list *delete(struct list *v, long x){
	struct list *inizio=v;
	if(v!=NULL){
		if(v->dato==x){
			inizio=v->fw;
			free(v);			
		}
		else{
			while(v->dato!=x && v->fw!=NULL) v=v->fw;
			if(v->dato==x){
				v->bw->fw=v->fw;
				if(v->fw!=NULL) v->fw->bw=v->bw;
				free(v);
			}
		}	
	}
	return inizio;
		
	
}






