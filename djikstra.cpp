#include<iostream>
#include<stdlib.h>
#include<cmath>
#include <stdio.h>
using namespace std;

struct vertex{
    long index;
    long weight;
    struct vertex* next;
};

struct vertex* new_node(long i,long w){
    struct vertex* node=new vertex;
    node->index=i;
    node->weight=w;
    return node;
}

struct vertex* add(long q,struct vertex* list,long w){
    struct vertex* current=list;
    if(current==NULL){
        return new_node(q,w);
    }
    else{
        struct vertex *newnode = new_node(q,w);
        newnode->next = list;
        list= newnode;
        return list;
    }
}

long min(long heap[],long v){
    long min=99999999,minindex;
    for(int i=0;i<v;i++){
        if(heap[i]<min){
            min=heap[i];
            minindex = i;
        }
            
    }
    return minindex; 
}

long Djikstra(struct vertex **list,long s,long e,long v,long heap[],long d[],long t){
    heap[s] = 0;
    d[s] = 0;
    bool found[v];
    for(long i=0;i<v;i++){
        found[i]=false;
    }
    
    for(long i=0;i<v;i++){
        long u = min(heap,v);
        heap[u] = 99999999;
        found[u]=true;
        struct vertex *current = list[u];
        while(current!=NULL){
            long v = current->index;
            long w = current->weight;
            if(d[v]>d[u] +w && found[v]!=true){
                d[v]=d[u]+w;
                heap[v] = d[v];
            }
            current=current->next;
        }
    }
    // cout<<d[t];
    return d[t];
}

int main(){
    long numvertex;
    cin>>numvertex;
    long numedges;
    cin>>numedges;    
    struct vertex* list[numvertex];
    long d[numvertex], heap[numvertex];
    for(long i=0;i<numvertex;++i){
        list[i]=NULL;
        heap[i] = 99999999;
        d[i] = 99999999;
    }
    // while(numedges--){
    //     long p,q,w;
    //     cin>>p>>q>>w;
    //     list[p]=add(q,list[p],w);
    // }
    for(long i=0;i<numedges;i++){
        long p,q;
        long w;
        scanf("%ld %ld %ld",&p,&q,&w);        
        list[p]=add(q,list[p],w);
    }
    // cout<<numedges;
    long s,t;
    scanf("%ld %ld",&s,&t); 
    // cout<<s<<t;
    long ans=0;
    ans=Djikstra(list,s,numedges,numvertex,heap,d,t);
    printf("%ld",ans);
    // for(long i=0;i<numvertex;++i){
    //     struct vertex* current=list[i];
    //     cout<<i<<"->";
    //     while(current!=NULL){
    //         printf("%d-%ld,",current->index,current->weight);
    //         current=current->next;
    //     }
    //     printf("\n");
    // }
}