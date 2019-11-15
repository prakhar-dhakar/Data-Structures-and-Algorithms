#include<iostream>
#include<stdlib.h>
using namespace std;

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

bool check_bipartite(vertex** list,bool found[],bool bicolor[]){
    int top=0,bottom=0;
    int *queue=new int;
    queue[top]=0;top++;
    found[0]=true;
    bicolor[0]=1;
    while(top!=bottom){
        int u = queue[bottom];
        bottom++;
        vertex* current = list[u];
        while(current!=NULL){
            if(found[current->index]==0){
                found[current->index]=1;
                bicolor[current->index]=!bicolor[u];
                queue[top] = current->index; top++;
                
            }
            else if(bicolor[current->index]==bicolor[u])
                return false;
        current = current->next;
        }
    }
    return true;
}

bool dfs_visit(long index,vertex **list, long bicolor[],char color[])
    {
        // cout<<index<<"dfs_visiting"<<color[0]<<endl;
        vertex* current = list[index];
        while(current!=NULL)
        {
            // cout<<current->index+1<<" current, index = "<<index+1<<endl;
            if(color[current->index]=='w'){
                color[current->index] = 'g';                    
                if(bicolor[index]==1)
                    bicolor[current->index]=0;
                else
                    bicolor[current->index]=1;
                
                if(!dfs_visit(current->index,list,bicolor,color))
                    return false;
            }
            else if(bicolor[current->index]==bicolor[index])
                return false;
            current = current->next;
        }
        // cout<<"finished "<<index<<endl;
        color[index] = 'b';
        return true;
    }



int main(){
    long n;
    cin>>n;
    for(long i=0;i<n;i++){
        long numvertex;
        cin>>numvertex;
        long numedges;
        cin>>numedges;
        
        long bicolor[numvertex];
        char color[numvertex];
        for(long i=0;i<numvertex;++i){
            color[i]='w';
            bicolor[i]=-1;
        }
        vertex* list[numvertex];
        for(long i=0;i<numvertex;++i){
            list[i]=NULL;
        }
        
        while(numedges--){
            long p,q;
            cin>>p>>q;
            // cout<<p<<" "<<q<<endl;
            list[p-1]=add(q-1,list[p-1]);
            list[q-1]=add(p-1,list[q-1]);
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
        for(int i=0;i<numvertex;i++){
            // cout<<color[i];
            if(color[i]=='w'){
                // cout<<i;
                ans = dfs_visit(i,list,bicolor,color);
                if(ans==false)
                    break;
            }
        }
        if(ans==1)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
        
        

    }
}