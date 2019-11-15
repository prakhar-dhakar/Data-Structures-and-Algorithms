#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Stack{
        int st[1000];
        int top=-1;
};
bool isEmpty(Stack* S){
    return (*S).top==-1;
}
bool isFull(Stack* S){
    return (*S).top==1000;
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
    if (isEmpty(S))
        return 'a';
    else 
        return (*S).st[(*S).top];
}

bool isOperator(char s)
{
    if(s=='+' || s=='-' || s=='*' || s=='/' || s=='%' || s=='^'||s=='('||s==')')
        return true;
    
    return false;
}

int Weight(char op)
{
    int weight = -1; 
    switch(op)
    {
    case '+':
    case '-':
        weight = 1;
        break;        
    case '*':
    case '/':
        weight = 2;
        break;
    case '^':
        weight = 3;
        break;
    }
    return weight;
}

int RightAss(char c)
{
    if(c == '^') return true;
    return false;
}

int HasHigherPrecedence(char op1, char op2)
{
    int op1Weight = Weight(op1);
    int op2Weight = Weight(op2);
    if(op1Weight == op2Weight)
    {
        if(RightAss(op1)) return false;
        else return true;
    }
    else if( op1Weight > op2Weight )
        return true;
    else
        return false;
}

string infixtopostfix(string str,int len){
    Stack *stack =  new Stack;
    string convert="";
    //int len = str.size();
    int i=0,j=0;
    int bracketcount=0;
    while(i<=len-1){
        if(!(isOperator(str[i]))){
            // cout<<"notop"<<str[i]<<endl;
            convert += str[i];
            i++;
            j++; 
        }
        else if(str[i]=='('){
            bracketcount++;
            Push(stack,str[i]);
            i++;
        }
        else if(bracketcount>0 && str[i]!=')'){            
            Push(stack,str[i]);
            i++;
        }
        else if(str[i]==')'){
            // cout<<Top(stack)<<endl;
            while(Top(stack)!='(' && !isEmpty(stack)){
                // cout<<Top(stack)<<endl;
                convert += Pop(stack);
                j++;
            }
            bracketcount--;
            Pop(stack);
            i++;
            // cout<<Top(stack)<<endl;
        }
        else{
            while(!isEmpty(stack) && HasHigherPrecedence(Top(stack),str[i])){
                // cout<<str[i]<<"emp"<<endl;
                convert += Pop(stack);
                j++;
            }
            // cout<<"last"<<str[i];
            Push(stack,str[i]);
            i++;
        }
    }
    while(!isEmpty(stack)){
        char x;
        
        x = Pop(stack);
        // cout<<'l'<<x<<endl;
        convert += x ;
        j++;
    }
    cout<<convert;
    return convert;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    string s,converted ;
    getline(cin,s);
    int len=s.size();
    converted = infixtopostfix(s,len);
    return 0;
}
