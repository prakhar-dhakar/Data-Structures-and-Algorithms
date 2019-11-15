struct minheapnode{
    int index;
    int w;
}
int heapsize=0;
int *pos;
void makeHeap(int v,int s){
    minheapnode *heap = new minheapnode[v] ;
    pos = new int[v];
    for(int i=0;i<v;i++){
        heap[i]->index=i;
        heap[i]->w=9999999;
        pos[i] = i;
        heapsize++;
    }
    heap[s]->w=0;    
}
int left(int i){ 
    return (i*2) + 1; 
    }
int right (int i){
    return (i*2) +2;
} 
int parent(int i){
    return (i-1)/2;
} 

void Heapify(minheapnode **heap,int i){
    int l = left(i);
    int r= right(i);
    int smallest;
    if(l<heapsize && heap[l]->w > heap[i]->w)
        smallest=l;
    else 
        smallest=i;
    if(r<heapsize && heap[r]->w > heap[smallest]->w)
        smallest=r;
    if(smallest!=i){
        pos[heap[smallest]->index] = i;
        pos[heap[i]->index]= smallest;
        swap(heap[i],heap[smallest]);
        Heapify(heap,smallest);
    }
}

int ExtractMin(minheapnode **heap){
    int min = heap[0]->index;
    swap(heap[0],heap[heapsize-1]);
    pos[heap[0]->index] = heapsize-1;
    pos[heap[heapsize-1]->index] = 0;
    heapsize--;
    Heapify(heap,0);
    return min;
}

void DecreaseKey(minheapnode **heap,int index, int value){
    int actualpos = pos[index];
    heap[actualpos]->w = value;
    while(actualpos!=0 && heap[parent(actualpos)]->w > heap[actualpos]->w){
        swap(heap[parent(actualpos)],heap[actualpos]);
        actualpos = parent(actualpos);
    }

}