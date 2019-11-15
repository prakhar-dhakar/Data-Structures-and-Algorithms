#include<iostream>
#include<stdlib.h>
using namespace std;

long count;
long* startedge;
long *finishedge;
long ttt=0;

struct vertex{
    long index;
    vertex* next;
};

vertex* new_node(long i){
    vertex* node=new vertex;
    node->index=i;
    return node;
}

vertex* add(long q,vertex* list){
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

void sort(long a[],long b[]){
    for(long i=0;i<count;i++){
        for(long j=i+1;j<count;j++){
            if(a[j]<a[i]){
                long temp1 = a[i];
                a[i] = a[j];
                a[j] = temp1;
                long temp2 = b[i];
                b[i] = b[j];
                b[j] = temp2;
            }
            else if(a[i] == a[j]){
                if(b[j]<b[i]){
                    long temp1 = a[i];
                    a[i] = a[j];
                    a[j] = temp1;
                    long temp2 = b[i];
                    b[i] = b[j];
                    b[j] = temp2;
               }
            }
        }
    }
}

long min(long a,long b){
    if(a>=b)
        return b;
    else
        return a;
}

bool dfs_visit(long index,vertex **list,char color[],long dtime[], long lowlink[],long parent[])
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



int main(){
    long numvertex;
    cin>>numvertex;
    long numedges;
    cin>>numedges;
    
    char color[numvertex];
    for(long i=0;i<numvertex;++i){
        color[i]='w';
    }
    vertex* list[numvertex];
    for(long i=0;i<numvertex;++i){
        list[i]=NULL;
    }

    while(numedges--){
        long p,q;
        cin>>p>>q;
        // cout<<p<<" "<<q<<endl;
        list[p]=add(q,list[p]);
        list[q]=add(p,list[q]);
    }
    // for(long i=0;i<numvertex;++i){
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
    long dtime[numvertex],lowlink[numvertex],parent[numvertex];
    startedge=new long;
    finishedge=new long;
    for(int i=0;i<numvertex;i++){
        // cout<<color[i];
        if(color[i]=='w'){
            // cout<<i;
            ans = dfs_visit(i,list,color,dtime,lowlink,parent);
        }
    }
    sort(startedge,finishedge);
    if(count==0)
        printf("No\n");
    else{
        for(long i=0;i<count;i++){
            printf("%d %d\n",startedge[i],finishedge[i]);
        }
    }
    // cout<<"No";
}