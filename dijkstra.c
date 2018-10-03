#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define M 1000000

struct nodo{
	int peso;
	struct nodelist *fs;
	bool inserito;
};

struct nodelist{
	int nd;
	int peso;
	struct nodelist *fw;
};

struct heapnode{
	int nd;
	int peso;
};
typedef struct heapnode heapnode;


void dijkstra(heapnode *todo, int *size, struct nodo* v, int actnd);
struct nodelist * add(struct nodelist *l, int to, int we);
int minPaFi(heapnode *hparr, int *hpsz, int i);
void scambia (heapnode *hparr, int i, int j);
void reorder(heapnode *hparr, int *hpsz, int i);
void enqueue(heapnode *hparr, int *hpsz, heapnode enter);
heapnode dequeue(heapnode *hparr, int *hpsz);

int main(){
	int n, m, i, from, to, we;
	struct nodo *v;
	heapnode *todo;
	int todosize=0;
	
	scanf("%d %d", &n, &m);
	v=(struct nodo*) malloc (sizeof(struct nodo)*n);
	todo=(heapnode *)malloc(sizeof(heapnode)*n);
	for(i=0; i<n; i++){
		v[i].peso=M;
		v[i].fs=NULL;
		v[i].inserito=false;
	}
	for(i=0; i<m; i++){
		scanf("%d %d %d", &from, &to, &we);
		v[from].fs=add(v[from].fs, to, we);
	}
	
	v[0].peso=0;
	dijkstra(todo, &todosize, v, 0);
	printf("%d\n", (v[n-1].peso<M ? v[n-1].peso : -1));

	return 0;
}


struct nodelist * add(struct nodelist *l, int to, int we){
	struct nodelist *p;
	p=(struct nodelist *) malloc (sizeof(struct nodelist));
	p->nd=to;
	p->peso=we;
	p->fw=l;
	return p;
}

void dijkstra(heapnode *todo, int *size, struct nodo* v, int actnd){
	struct nodelist *p=v[actnd].fs;
	heapnode w;
	while(p!=NULL){
		if(v[actnd].peso+p->peso<v[p->nd].peso){
			v[p->nd].peso=v[actnd].peso+p->peso;
			w.nd=p->nd;
			w.peso=v[p->nd].peso;
			if(v[p->nd].inserito==false) enqueue(todo, size, w);
			v[p->nd].inserito=true;
		}
		p=p->fw;
	}
	if(*size>0) {
		w=dequeue(todo, size);
		dijkstra(todo, size, v, w.nd);
	}
		
}

void enqueue(heapnode *hparr, int *hpsz, heapnode enter){
	hparr[(*hpsz)++]=enter;
	reorder(hparr, hpsz, *hpsz-1);		
}

heapnode dequeue(heapnode *hparr, int *hpsz){
	heapnode minimo=hparr[0];
	hparr[0]=hparr[--(*hpsz)];
	reorder(hparr, hpsz, 0);
	return minimo;
	
}

void reorder(heapnode *hparr, int *hpsz, int i){
	int figlio;
	while(i>0 && hparr[i].peso<hparr[(i-1)/2].peso){
		scambia(hparr, i, (i-1)/2);
		i=(i-1)/2;
	}
	/*ricordiamo che le espressioni booleane in C vengono valutate da sinistra a destra*/	
	while(2*i+1< *hpsz && i!=minPaFi(hparr, hpsz, i)){
		figlio=minPaFi(hparr, hpsz, i);
		scambia(hparr, figlio, i);
		i=figlio;
	}

}

int minPaFi(heapnode *hparr, int *hpsz, int i){
	int j, k;
	j=k=2*i+1;
	if(k+1<*hpsz) k++;
	if(hparr[i].peso<hparr[j].peso) j=i;
	if(hparr[k].peso<hparr[j].peso) j=k;
	return j;
}

void scambia (heapnode *hparr, int i, int j){
	heapnode tmp;
	tmp=hparr[i];
	hparr[i]=hparr[j];
	hparr[j]=tmp;
}







