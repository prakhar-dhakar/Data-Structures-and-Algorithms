void dfs(node *curr,int dest,int w,node *tree,int max_so_far,int p,int *ans){
    int tmp=max_so_far,vertex=curr->vert;
    curr=curr->next;
    while(curr!=NULL && flag){
        if(curr->vert!=p){
           // cout<<vertex<<" "<<curr->vert<<"\n";
            if(curr->wt > max_so_far){
                e1=vertex;
                e2=curr->vert;
                max_so_far=curr->wt;
            }
            if(curr->vert==dest){
                flag=false;
                if(max_so_far > w){
                 //   cout<<"sdsmbsm";
                 //   addedge(source,dest,&ptr[source],&ptr[dest],w);
                    (*ans)-=max_so_far-w;
                }
                return ;
            }
            dfs(&tree[curr->vert],dest,w,tree,max_so_far,vertex,ans);
        }
        max_so_far=tmp;
        curr=curr->next;
    }
    return ;
}

bool flag=true;
int dfs_visit(int max,int v,int index,vertex **list,char color[])
    {
        // cout<<index<<"dfs_visiting"<<color[0]<<endl;
        vertex* current = list[index];
        int t = max;
        int a;
        while(current!=NULL && flag)
        {
            // cout<<current->index+1<<" current, index = "<<index+1<<endl;
            if(color[current->index]=='w'){
                color[current->index] = 'g';
                if(current->weight >max){
                    max=current->weight;
                }
                if(current->index == v){
                    flag=false;
                    return max;
                }
                a = dfs_visit(max,v,current->index,list,color);                
            }
            max=t;
            current=current->next;
        }
        return a;
    }