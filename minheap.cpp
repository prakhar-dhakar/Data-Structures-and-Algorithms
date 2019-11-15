class MinHeap{
    private:
        vector<int> arr;
        vector<int> ind; 
        int heap_size; 
        int left(int i){ 
            return (i*2) + 1; 
        }
        int right (int i){
            return (i*2) +2;
        } 
        int parent(int i){
            return (i-1)/2;
        }        
    public:
    MinHeap(int s,int v){ 
        heap_size = 0;
        for(int j=0;j<v;j++){
            arr[j] = 99999999;
            ind[j]=j;
        }
        arr[s]=0;
    Makeminheap();
    }    
    void Makeminheap(){
        for(int i=(arr.size()+1)/2;i>=0;i--){
            Heapify(i);
        }
    }
    void Heapify(int i){
        int l=left(i);  
        int r=right(i); 
        int smallest = i; 
        
        if(l < arr.size() and arr[l] <  arr[i])
            smallest = l ; 
        if(r<arr.size() and arr[r] <  arr[i])
            smallest = r; 
        if(smallest != i){
            swap(arr[smallest],arr[i]);
            swap(ind[smallest],ind[i]);
            Heapify(i);
        }
    }
    
    void insertKey(int val){
        arr.push_back(val); 
        int curr_elem_pos = arr.size()-1; 
        while(curr_elem_pos !=0 and arr[parent(curr_elem_pos)] > arr[curr_elem_pos]){
            swap(arr[parent(curr_elem_pos)],arr[curr_elem_pos]); 
            cout<<"swapping:" <<"\n"; 
            
            cout<<arr[parent(curr_elem_pos)] <<" "<<arr[curr_elem_pos]<<"\n"; 
            
            curr_elem_pos = parent(curr_elem_pos); 
            
        }
        
    }
    
    int getMin(){
        return arr.at(0); 
    }
    
    int extractMin(){
        int min_val = arr[0];        
        swap(arr[0],arr[arr.size()-1]);
        swap(ind[0],ind[arr.size()-1]);
        ind.pop_back();
        arr.pop_back();
        Heapify(0);
        return min_val; 
    }
    
    void decreaseKey(int index, int value){ // a chance to become root, so bubble up 
        arr[index] = value; 
        while(index !=0 and arr[parent(index)] > arr[index]){
            swap(arr[parent(index)], arr[index]);
            swap(ind[parent(index)],index[arr[index]]);
            index = parent(index); 
        }
    }
    
    void deleteKey(int index){
        decreaseKey(index,INT_MIN); // promote to root 
        extractMin();      // delete the root 
        
    }
        
};