#include<iostream>
// #include<stdlib.h>
// #include<cmath>
#include<stdio.h>
using namespace std;


int main() {
    int n;
    scanf("%ld",&n);
    char temp;
    while(n--){
        int l1,l2;
        scanf("%ld %ld",&l1,&l2);
        // printf("%ld %ld",l1,l2);
        char s1[l1],s2[l2];        
        
        scanf("%c",&temp);

        for(int i=0;i<l1;i++){
            scanf("%c",&s1[i]);
        }
        
        scanf("%c",&temp);

        
        for(int j=0;j<l2;j++){
            scanf("%c",&s2[j]);
        }
        
        
        // for(int i=0;i<l1;i++){
        //     printf("%c",s1[i]);
        // }
        // for(int j=0;j<l2;j++){
        //     printf("%c",s2[j]);
        // }
        
        int *ans[l1+1]; 
        for (int i=0;i<=l1;i++) 
             ans[i]=(int *)malloc((l2+1)*sizeof(int));
        // ans[0][0]=1;
        // for(int i=2;i<=l1;i++){
        //     for(int j=2;j<=l2;j++){
        //         // s1[i-1]='a';
        //         // s2[j-1]='a';
        //         // printf("%ld %ld",i,j);
        //         // sum=sum+i+j;
        //     }
        // }
        
        for(int i=0;i<=l1;i++){
            for(int j=0;j<=l2;j++){
                if(i==0 || j==0)
                    ans[i][j]=0;
                else {
                    if(s1[i-1]==s2[j-1])
                        ans[i][j] = ans[i-1][j-1]+1;
                    else{
                        if(ans[i-1][j]>ans[i][j-1])
                            ans[i][j]=ans[i-1][j];
                        else
                            ans[i][j]=ans[i][j-1];
                    }
                }
            }
        }
        printf("%ld\n",ans[l1][l2]);
    }
    return 0;
}
