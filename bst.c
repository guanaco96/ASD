/*Programma che implementa un AVL (ovveru un BinarySearchTree 1-bilanciato come albero binario di ricerca*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define max(a,b) a>b ? a : b

struct nodo{
	long label; 
	struct nodo *sx;
	struct nodo *dx;
	long alt;
	bool vivo;
	long elem_sx;
	long elem_dx;
};

struct opera{
	char tipo;
	long numero;
	long in;
	long fi;
};

void stampalo(struct nodo*);

long contaminori( struct nodo *p, long in, long fi);
long contamaggiori( struct nodo *p, long in, long fi);
long inserisciV (long *v, long n, struct nodo *p);
struct nodo* ruotaAnti(struct nodo *p);
struct nodo* ruotaOraria(struct nodo *p);
struct nodo * nuovonodo(long x);
struct nodo* inserisci(struct nodo *p, long x, bool *exNovo);
long altezza(struct nodo *p);
void aggiornAlt(struct nodo *p);
int trova (struct nodo *p, long x);
bool delete(struct nodo *p, long x);
long range(struct nodo *p, long in, long fi);


int main(){
	long n, o, i, dato;
	bool exNovo;
	struct nodo *p=NULL;	
	
	scanf("%ld %ld", &n, &o);
	
	long *v=(long *) malloc (sizeof(long)*n);
	struct opera w[o];
	
	for(i=0; i<n; i++) scanf("%ld", &v[i]);
	
	p=(struct nodo*) malloc (sizeof(struct nodo));
	if(n>0) p->alt=inserisciV(v, n, p);
	else p=NULL;

		
	for(i=0; i<o; i++){
		while((w[i].tipo=getchar())=='\n');
		if(w[i].tipo!='r') scanf("%ld", &w[i].numero);
		else scanf("%ld %ld", &w[i].in, &w[i].fi);
	}
	
	for (i=0; i<o; i++) {
		if(w[i].tipo=='f') printf("%d\n", trova(p, w[i].numero));
		if(w[i].tipo=='i') p=inserisci(p, w[i].numero, &exNovo);
		if(w[i].tipo=='d') delete(p, w[i].numero);
		if(w[i].tipo=='r') printf("%ld\n", range(p, w[i].in, w[i].fi));
		
	
	}
	//stampalo(p);
			
	return 0;
}

void stampalo (struct nodo*p){
	//visita simmetrica
	if(p->sx!=NULL) stampalo(p->sx);
	printf("elemento %ld\t altezza %ld\t vivo=%d\t elem_sx= %ld\t elem_dx=%ld\n", p->label, p->alt, p->vivo, p->elem_sx, p->elem_dx);
	if(p->dx!=NULL) stampalo(p->dx);
}

long inserisciV (long *v, long n, struct nodo *p){
	long half=(n+1)/2-1;
	long hsx=-1, hdx=-1;
	if(n!=0){
		p->vivo=true;		
		p->label=v[half];
		if(half>0){ 
			p->sx=(struct nodo*) malloc (sizeof(struct nodo));
			hsx=inserisciV(v, half, p->sx);
			p->elem_sx=half;
		}
		else {
			p->sx=NULL;
			p->elem_sx=0;
		}
		
		if(n>1){
			p->dx=(struct nodo*) malloc (sizeof(struct nodo));
			hdx=inserisciV(&v[half+1], n-half-1, p->dx);
			p->elem_dx=n-half-1;
		}
		else {
			p->dx=NULL;
			p->elem_dx=0;
		}
	}
	return p->alt=max(hsx+1,hdx+1);
}

long altezza(struct nodo *p){
	if(p==NULL) return -1;
	else return p->alt;
}

void aggiornAlt(struct nodo *p){
	p->alt=max(altezza(p->sx)+1, altezza(p->dx)+1);
}

struct nodo * nuovonodo(long x){
	struct nodo *p;
	p=(struct nodo*) malloc (sizeof(struct nodo));
	p->label=x;
	p->sx=p->dx=NULL;
	p->alt=0;
	p->vivo=true;
	p->elem_sx=p->elem_dx=0;
	return p;
}

struct nodo* ruotaOraria(struct nodo *p){
	struct nodo *tmp=p->sx->dx, *newP=p->sx;
	p->elem_sx=p->sx->elem_dx;
	p->sx->elem_dx+=(p-> vivo ? 1 : 0) + p->elem_dx;
	p->sx->dx=p;
	p->sx=tmp;
	aggiornAlt(p);
	aggiornAlt(newP);
	
	return newP;
}

struct nodo* ruotaAnti(struct nodo *p){
	struct nodo *tmp=p->dx->sx, *newP=p->dx;
	p->elem_dx=p->dx->elem_sx;
	p->dx->elem_sx+=(p->vivo ? 1 : 0) + p->elem_sx;
	p->dx->sx=p;
	p->dx=tmp;
	aggiornAlt(p);
	aggiornAlt(newP);
	
	return newP;
}

struct nodo * inserisci(struct nodo *p, long x, bool * exNovo){
	if (p==NULL){
		*exNovo=true;
		return nuovonodo(x);
	}
	else{
		if(x<p->label){
			p->sx=inserisci(p->sx, x, exNovo);
			if (*exNovo) p->elem_sx++;
			/*if(altezza(p->sx)-altezza(p->dx)==2){
				if(x>p->sx->label) p->sx=ruotaAnti(p->sx);
				p=ruotaOraria(p);							
			}
			else*/ aggiornAlt(p);
		}
		if(x>p->label){
			p->dx=inserisci(p->dx, x, exNovo);
			if(*exNovo) p->elem_dx++;
			/*if(altezza(p->dx)-altezza(p->sx)==2){
				if(x<p->dx->label) p->dx=ruotaOraria(p->dx);
				p=ruotaAnti(p);							
			}
			else*/ aggiornAlt(p);
		
		}
		if(p->label==x) {
			if(p->vivo==true) *exNovo=false;
			else {
				p->vivo=true;
				*exNovo=true;
			}
		}
			
	}
	return p;
}




int trova (struct nodo *p, long x){
	if (p==NULL) return 0;
	if(x==p->label) return p->vivo ? 1 : 0;
	else{
		if(x<p->label) return trova(p->sx, x);
		else return trova(p->dx, x);
	}
}

/*delete restituisce: "ho eleiminato un elemento?"*/

bool delete (struct nodo* p, long x){
	bool b;
	if (p!=NULL){
		if(x==p->label){
			b=p->vivo;
			p->vivo=false;
			return b;
		}
		else{
			if(x<p->label){
				b=delete(p->sx, x);
				if(b==true) p->elem_sx--;
				return b;
			}
			else{
				b=delete(p->dx, x);
				if(b==true) p->elem_dx--;
				return b;
			}
		}
	}
	else return false;
}

long contamaggiori( struct nodo *p, long in, long fi){
	if(p==NULL) return 0;
	if(p->label>=in) return p->elem_dx+ (p->vivo ? 1 : 0) +contamaggiori(p->sx, in, fi);
	else  return contamaggiori(p->dx, in, fi);
	
}

long contaminori( struct nodo *p, long in, long fi){
	if(p==NULL) return 0;
	if(p->label<fi) return p->elem_sx+ (p->vivo ? 1 : 0) +contaminori(p->dx, in, fi);
	else return contaminori(p->sx, in, fi);
}

long range(struct nodo *p, long in, long fi){
	if(p==NULL) return 0;
	if (in<=p->label && fi>p->label) return (p->vivo? 1 : 0 ) + contamaggiori(p->sx, in, fi) + contaminori (p->dx, in, fi);
	if(fi<=p->label) return range(p->sx, in, fi);
	if(in>p->label) return range(p->dx, in, fi);
}

