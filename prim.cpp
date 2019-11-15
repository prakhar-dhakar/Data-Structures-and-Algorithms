#include<iostream>
#include<stdlib.h>
#include<cmath>

using namespace std;

struct vertex{
    int index;
    int weight;
    struct vertex* next;
};

struct vertex* new_node(int i,int w){
    struct vertex* node=new vertex;
    node->index=i;
    node->weight=w;
    return node;
}

struct vertex* add(int q,struct vertex* list,int w){
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

int min(int heap[],int v){
    int min=999999,minindex=0;
    for(int i=0;i<v;i++){
        if(heap[i]<min){
            min=heap[i];
            minindex = i;
        }
            
    }
    // cout<<min<<"min-u"<<minindex<<endl;
    return minindex; 
}

struct node{
    int parent;
};

void remove(vertex **list, int index1, int index2){
    vertex* current=list[index1];
    vertex* prev;
    prev=NULL;
    while(current!=NULL){
        if(current->index == index2){
            if(prev!=NULL)
              prev->next = current->next;
            else
                list[index1] = current->next;
            break;
        }
        prev=current;
        current=current->next;
    }
    
    current=list[index2];
    prev=NULL;
    while(current!=NULL){
        if(current->index == index1){
            if(prev!=NULL)
              prev->next = current->next;
            else
                list[index2] = current->next;
            break;
        }
        prev=current;
        current=current->next;
    }    
}

int Djikstra(struct vertex **list,int s,int e,int v,int heap[],int d[],struct vertex **mst){
    bool found[v];
    int tree[v];
    for(int i=0;i<v;i++){
        heap[i]=999999;
        d[i] = 999999;
        found[i]=false;
        tree[i]=-1;
    }
    heap[s] = 0;
    d[s] = 0;
    for(int i=0;i<v;i++){
        int u = min(heap,v);
        // cout<<u<<"u"<<endl;
        heap[u] = 99999999;
        found[u]=true;
        struct vertex *current = list[u];
        while(current!=NULL){
            int v = current->index;
            int w = current->weight;
            if(d[v]>w && found[v]!=true){
                d[v]=w;
                heap[v] = d[v];
                tree[v]=u;
            }
            current=current->next;
        }
    }
    // cout<<d[t];
    int sum=0;
    for(int i=0;i<v;++i){
        mst[i]=NULL;
    }
    for(int i=0;i<v;i++){
        sum=sum+d[i];
        if(tree[i]!=-1){
            mst[i]=add(tree[i],mst[i],d[i]);
            mst[tree[i]]=add(i,mst[tree[i]],d[i]);
        }
    }
    return sum;
}

bool flag=true;
int edge1,edge2;

void dfs_visit(int v,int index,vertex **list,char color[],int parent[])
    {
       // cout<<"max"<<max<<endl;        // cout<<index<<"dfs_visiting"<<color[0]<<endl;
        vertex* current = list[index];
        while(current!=NULL && flag)
        {
            // cout<<current->index+1<<" current, index = "<<index+1<<endl;
            if(color[current->index]=='w'){
                color[current->index] = 'g';
                parent[current->index]=index;
                dfs_visit(v,current->index,list,color,parent);                
            }
            if(current->index==v){
                flag=false;
            }
            current=current->next;
        }
        return ;
    }

int main(){
    int numvertex;
    scanf("%d",&numvertex);
    int numedges;
    scanf("%d",&numedges);
    int q;
    scanf("%d",&q);
    struct vertex* list[numvertex];
    int d[numvertex],heap[numvertex];
    for(int i=0;i<numvertex;++i){
        list[i]=NULL;
    }

    while(numedges--){
        int p,r,w;
        scanf("%d %d %d",&p,&r,&w);
        list[p]=add(r,list[p],w);
        list[r]=add(p,list[r],w);
    }
    
    vertex *mst[numvertex];
    
    
    int ans=Djikstra(list,0,numedges,numvertex,heap,d,mst);
    printf("%d\n",ans);
    
    // for(int i=0;i<numvertex;++i){
    //     struct vertex* current=mst[i];
    //     cout<<i<<"->";
    //     while(current!=NULL){
    //         printf("%d-%ld,",current->index,current->weight);
    //         current=current->next;
    //     }
    //     printf("\n");
    // }
    
    while(q--){
        int p,r,w;
        scanf("%d %d %d",&p,&r,&w);
        // mst[p]=add(r,mst[p],w);
        // mst[r]=add(p,mst[r],w);
        char color[numvertex];
        int parent[numvertex];
        for(int i=0;i<numvertex;i++){
            color[i]='w';
            parent[i]=-1;
        }
        flag=true;
        dfs_visit(r,p,mst,color,parent);
        int lv=r;
        int maxwt=0;
        while(lv!=p){
            vertex *current = mst[parent[lv]];
            int wt;
            while(current->index!=lv){
                current=current->next;
            }
            wt = current->weight;
            if(wt>maxwt){
                maxwt=wt;
                edge1=lv;
                edge2=parent[lv];
            }
            lv=parent[lv];
        }
        // cout<<maxwt<<endl;
        // cout<<"edge1 "<<edge1;
        // cout<<" edge2 "<<edge2<<endl;
        if(w<maxwt){
            remove(mst,edge1,edge2);
            remove(mst,edge2,edge1);
            mst[p]=add(r,mst[p],w);
            mst[r]=add(p,mst[r],w); 
            ans = ans-maxwt+w;
        }
        
        // int ans=Djikstra(mst,0,numedges,numvertex,heap,d,mst);
        printf("%d\n",ans);
    }
    // for(int i=0;i<numvertex;++i){
    //     struct vertex* current=mst[i];
    //     cout<<i<<"->";
    //     while(current!=NULL){
    //         printf("%d-%ld,",current->index,current->weight);
    //         current=current->next;
    //     }
    //     printf("\n");
    // }
}