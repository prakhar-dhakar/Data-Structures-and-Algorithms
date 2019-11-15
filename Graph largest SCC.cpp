#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int ttt=0;

int *stack;
int stacktop = 0;
struct node{
    int data;
    struct node *next;
};

struct vertexlist{
    char color = 'w';
    int d;
    int f;
    struct node *vertexhead = new node;
};

struct Graph{
    int vertex;
    struct vertexlist *vl = new vertexlist;    
};

void DFS_visit(struct Graph *G,int x){
    ttt +=1;
    G->vl[x].d = ttt;
    G->vl[x].color = 'g';
    struct node *v = new node;
    v = G->vl[x].vertexhead;
    while (v!=NULL){
        if( G->vl[v->data].color == 'w')
            DFS_visit(G,v->data);
        v = v->next;
    }
    G->vl[x].color = 'b';
    ttt+=1;
    G->vl[x].f = ttt;
    stack[stacktop] = x;
    stacktop++;
}

void DFS_visit2(struct Graph *G,int x){
    ttt +=1;
    G->vl[x].d = ttt;
    G->vl[x].color = 'g';
    struct node *v = new node;
    v = G->vl[x].vertexhead;
    while (v!=NULL){
        if( G->vl[v->data].color == 'w')
            DFS_visit(G,v->data);
        v = v->next;
    }
    G->vl[x].color = 'b';
    ttt+=1;
    G->vl[x].f = ttt;
}

void DFS(struct Graph *G){
    for(int i=0;i< G->vertex ;i++){
        if(G->vl[i].color == 'w')
            DFS_visit(G,i);
    }
}


int DFStwo(struct Graph *G,int stack[],int num){
    int sum=0,maxsum=0;
    // cout<<stack[0];
    for(int i=num-1;i>=0 ;i--){
        if(G->vl[stack[i]].color == 'w'){
            sum=1;
            // cout<<"sum = "<<sum<<endl;
            DFS_visit2(G,stack[i]);
        }
        else{
            sum = sum+1;
            if(sum>maxsum)
                maxsum= sum;
        }
            
    }
    return maxsum;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin>>n;
    for (int i=0;i<n;i++){
        int numvertexes,numedges;
        ttt=0;
        cin>>numvertexes;
        cin>>numedges;
        stack = new int[numvertexes];
        
        struct Graph *G = new Graph;
        struct Graph *Gtrans = new Graph;
        
        G->vertex = numvertexes;
        G->vl = new vertexlist[numvertexes];  
        
        Gtrans->vertex = numvertexes;
        Gtrans->vl = new vertexlist[numvertexes];
        
        for (int i=0;i<numedges;i++){   
            G->vl[i].vertexhead = NULL;
            Gtrans->vl[i].vertexhead = NULL;
        }
        for(int i=0;i<numedges;i++){
            int one,two;
            cin>>one;
            cin>>two;
            
            struct node *newnode = new node;
            newnode->data = two;
            newnode->next = NULL;
            if(G->vl[one].vertexhead == NULL)
                G->vl[one].vertexhead = newnode; 
            else{
                newnode->next = G->vl[one].vertexhead;
                G->vl[one].vertexhead = newnode;
            }
            
            struct node *newnode2 = new node;
            newnode2->data = one;
            newnode2->next = NULL;
            if(Gtrans->vl[two].vertexhead == NULL)
                Gtrans->vl[two].vertexhead = newnode2; 
            else{
                newnode2->next = Gtrans->vl[two].vertexhead;
                Gtrans->vl[two].vertexhead = newnode2;
            }
        }
        for(int i = 0; i < numedges; i++)
        {
            cout<<"\n\tV("<<i<<") -> {  ";
            struct node *pointer = new node;
            pointer = Gtrans->vl[i].vertexhead;
            while(pointer != NULL)
            {
                cout<<Gtrans->vl[i].color;
                cout<<pointer->data<<"  ";
                pointer = pointer->next;
            }
            cout<<"}";
        }
        DFS(G);
        int stackperm[numvertexes];
        for(int i = 0; i < stacktop; i++)
        {   
            stackperm[i] = stack[i];
            // cout<<stack[i];
        }
        // for(int i =0; i<numvertexes;i++ ){
        //     G->vl[i].color = 'w';
        // }
        
        cout<<DFStwo(Gtrans,stackperm,stacktop)<<endl;
        
        
    }
    return 0;
}
// 2
// 5
// 5
// 0 1
// 1 2
// 2 3
// 3 4
// 4 0
// 4
// 5
// 0 1
// 0 3
// 1 2
// 2 0
// 2 3