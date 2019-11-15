#include<iostream>
#include<stdlib.h>
using namespace std;

int count;
int* startedge;
int *finishedge;
int ttt=0;

struct vertex{
    int index;
    vertex* next;
};

vertex* new_node(int i){
    vertex* node=new vertex;
    node->index=i;
    return node;
}

vertex* add(int q,vertex* list){
    vertex* current=list;
    if(current==NULL){
        return new_node(q);
    }
    else{
        vertex *newnode = new_node(q);
        newnode->next = list;
        list= newnode;
        return list;
    }
}

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

int min(int a,int b){
    if(a>=b)
        return b;
    else
        return a;
}

bool dfs_visit(int index,vertex **list,char color[],int dtime[], int lowlink[],int parent[])
    {
        ttt++;
        dtime[index]=ttt;
        lowlink[index]=ttt;
        // cout<<index<<"dfs_visiting"<<color[0]<<endl;
        vertex* current = list[index];
        while(current!=NULL)
        {
            // cout<<current->index+1<<" current, index = "<<index+1<<endl;
            if(color[current->index]=='w'){
                
                color[current->index] = 'g';
                parent[current->index]=index;
                
                dfs_visit(current->index,list,color,dtime,lowlink,parent);
                
                lowlink[index] = min(lowlink[index],lowlink[current->index]);
                
                if(lowlink[current->index]>dtime[index]){
                    startedge[count] = index;
                    finishedge[count]=current->index;
                    count++;
                }                    
                
            }
            else if(current->index == parent[index])
            {   
            }
            else{
                lowlink[index]=min(lowlink[index],dtime[current->index]);
            }
            current = current->next;
        }
        // cout<<"finished "<<index<<endl;
        color[index] = 'b';
        return true;
    }

void bfs(int index,vertex** list,bool found[],int dtime[]){
    int front=0,back=0;
    int *queue = new int[1000000];
    queue[back]=index;back++;
    found[index]=true;
    dtime[index]=0;
    while(front!=back){
        int u = queue[front];
        // cout<<"exploring"<<u<<endl;
        front++;
        vertex* current = list[u];
        while(current!=NULL){
            if(found[current->index]==0){
                found[current->index]=1;
                // cout<<"dtime current index = "<<dtime[index]+1<<" "<<current->index<<" index is "<<index<<endl;
                dtime[current->index]=dtime[u] +1;
                queue[back] = current->index; back++;
            }
        current = current->next;
        } 
    }
}


int main(){
    int numvertex;
    cin>>numvertex;
    int numedges;
    cin>>numedges;
    int cases;
    cin>>cases;
    char color[numvertex];
    bool found[numvertex];
    for(int i=0;i<numvertex;++i){
        color[i]='w';
        found[i] = false;
    }
    vertex* list[numvertex];
    for(int i=0;i<numvertex;++i){
        list[i]=NULL;
    }

    while(numedges--){
        int p,q;
        cin>>p>>q;
        // cout<<p<<" "<<q<<endl;
        list[p]=add(q,list[p]);
        list[q]=add(p,list[q]);
    }
    // for(int i=0;i<numvertex;++i){
    //     vertex* current=list[i];
    //     cout<<i<<"->";
    //     while(current!=NULL){
    //         printf("%d-",current->index);
    //         current=current->next;
    //     }
    //     printf("\n");
    // }
    // cout<<endl;
    bool ans;
    count=0;
    int dtime[numvertex],lowlink[numvertex],parent[numvertex];
    startedge=new int;
    finishedge=new int;
    for(int i=0;i<numvertex;i++){
        // cout<<color[i];
        if(color[i]=='w'){
            // cout<<i;
            ans = dfs_visit(i,list,color,dtime,lowlink,parent);
        }
    }
    // cout<<startedge[0]<<" "<<finishedge[0]<<endl<<endl;
    remove(list,startedge[0],finishedge[0]);
    
    int bfsdtime[numvertex];
    bfs(startedge[0],list,found,bfsdtime);
    bfs(finishedge[0],list,found,bfsdtime);
    
    for(int i=0;i<cases;i++){
        int one,two;
        cin>>one;
        cin>>two;
        cout<<bfsdtime[one]+bfsdtime[two]+1<<endl;
    }
    // for(int i=0;i<numvertex;++i){
    //     vertex* current=list[i];
    //     cout<<i<<"->";
    //     while(current!=NULL){
    //         printf("%d-",current->index);
    //         current=current->next;
    //     }
    //     printf("\n");
    // }
    // cout<<endl;
    
}