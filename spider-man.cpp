#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Stack{
        long int st[1000000];
        long int top=-1;
};
bool isEmpty(Stack* S){
    return (*S).top==-1;
}
bool isFull(Stack* S){
    return (*S).top==1000000;
}
void Push(Stack* S,char v){
    if(isFull(S))
        cout<<"Overflow";
    else{
        (*S).top= (*S).top+1;
        S->st[(*S).top] = v;
        // cout<<v<<endl;
    }
}
char Pop(Stack* S){
    if (isEmpty(S)){
        cout<<"Underflow";
        return '0';
    }
    else{
        char x;
        x = (*S).st[(*S).top];
        (*S).top = (*S).top-1;
        // cout<<x;
        return x;
    }
}

char Top(Stack* S){
    if (isEmpty(S)){
        cout<<"Underflow";
        return '0';
    }
    else 
        return (*S).st[(*S).top];
}

void Jump(long int building[],long int k){
    Stack* span = new Stack;
    long int num[k+1],h[k+1];
    for(long int i=0;i<=k;i++){
        while(!isEmpty(span)  && building[i] >= building[Top(span)]){
            Pop(span);
        }
        if(isEmpty(span)){
            Push(span,i);
            h[i] = i+1;
            num[i] = i+1;
        }
        else{
            h[i] = Top(span);
            Push(span,i);
            num[i] = i-h[i];#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Stack{
        long int st[1000000];
        long int top=-1;
};
bool isEmpty(Stack* S){
    return (*S).top==-1;
}
bool isFull(Stack* S){
    return (*S).top==1000000;
}
void Push(Stack* S,char v){
    if(isFull(S))
        cout<<"Overflow";
    else{
        (*S).top= (*S).top+1;
        S->st[(*S).top] = v;
        // cout<<v<<endl;
    }
}
char Pop(Stack* S){
    if (isEmpty(S)){
        cout<<"Underflow";
        return '0';
    }
    else{
        char x;
        x = (*S).st[(*S).top];
        (*S).top = (*S).top-1;
        // cout<<x;
        return x;
    }
}

char Top(Stack* S){
    if (isEmpty(S)){
        cout<<"Underflow";
        return '0';
    }
    else 
        return (*S).st[(*S).top];
}

void Jump(long int building[],long int k){
    Stack* span = new Stack;
    long int num[k+1],h[k+1];
    for(long int i=0;i<=k;i++){
        while(!isEmpty(span)  && building[i] >= building[Top(span)]){
            Pop(span);
        }
        if(isEmpty(span)){
            Push(span,i);
            h[i] = i+1;
            num[i] = i+1;
        }
        else{
            h[i] = Top(span);
            Push(span,i);
            num[i] = i-h[i];
        }       
    }
    for(long int i=1;i<=k;i++){
        printf("%d\n",num[i]);
    }  
    
}

int main() {
    long int n;
    cin>>n;
    for (long int i=0;i<n;i++){
        long int k;
        cin>>k;
        long int building[k];
        building[0] = 9999999999999;
        for(long int j=1;j<=k;j++){
            cin>>building[j];
        }
        Jump(building,k);
    }   
    return 0;
}
        }       
    }
    for(long int i=1;i<=k;i++){
        printf("%d\n",num[i]);
    }  
    
}

int main() {
    long int n;
    cin>>n;
    for (long int i=0;i<n;i++){
        long int k;
        cin>>k;
        long int building[k];
        k[0] = 9999999999999;
        for(long int j=1;j<=k;j++){
            cin>>building[j];
        }
        Jump(building,k);
    }   
    return 0;
}