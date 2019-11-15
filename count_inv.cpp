#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long count1 = 0;

long* merge(long first[],long second[],long len){
    long* sorted_array = (long*)malloc(sizeof(long)*len);
    long j=0,k=0;
    for(long i=0;i<len;i++){
        if (j == long(len/2)){
            while(i<len){
                sorted_array[i] = second[k];
                k++;
                i++;
            }
            break;
        }
        else if (k == (len - long(len/2))){
            while(i<len){
                sorted_array[i] = first[j];
                j++;
                i++;
            }
            break;
        }
        else if (first[j] <= second[k]){
            sorted_array[i] = first[j];
            j++;
            }
        else if (second[k] < first[j]){
            sorted_array[i] = second[k];
            count1 = count1 + len/2 - j ;
            k++;
        }
    }
    return sorted_array;
}

long* count_inversions(long arr[],long len){
    if(len<=1)
        return arr;
   else{
       long first_half[len/2],second_half[len - len/2];
       long* sorted_first_half,*sorted_second_half;
       
       for(long i=0;i<len;i++){
           
           if(i<long(len/2))
               first_half[i] = arr[i];
           else
               second_half[i-long(len/2)] = arr[i];
           
       }
       
       sorted_first_half = count_inversions(first_half,long(len/2));
       sorted_second_half = count_inversions(second_half,(len - long(len/2) ));
       
       return merge(sorted_first_half,sorted_second_half,len);
       
   }
}

int main() {
    /* Enter your code here. Read input from STDIN. Prlong output to STDOUT */   
    long n;
    cin>>n;
    
    for(long i=0;i<n;i++){
        long len;
        cin>>len;
        long arr[len];
        for(long i=0;i<len;i++){
            cin>>arr[i];
        }
        
        long *sorted;
        sorted = count_inversions(arr,len);
        // for (long i=0;i<len;i++)
        //     cout<<sorted[i]<<" ";
        cout<<count1;
        cout<<"\n";
        count1 = 0;
        
    }
    return 0;
}
