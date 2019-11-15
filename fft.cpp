#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <complex>
#include <vector>

using namespace std;

vector<complex<double>> Recursive_FFT(vector<complex<double>> A){
    int l = A.size();
    if(l==1){
        // cout<<A[0]<<"he";
        return A;
    }
    double alpha = 2*M_PI/l;
    complex<double> w(1,0) , wn(cos(alpha),sin(alpha));
    vector<complex<double>> even(l/2);
    vector<complex<double>> odd(l/2);
    for (int i=0;i<l/2;i++){
        even[i] = A[2*i];
        odd[i] = A[2*i+1];
    }
    vector<complex<double>> y_even =Recursive_FFT(even);;
    vector<complex<double>> y_odd =Recursive_FFT(odd);
    vector<complex<double>> y(l);
    for (int i=0;i< l/2 ;i++){
        y[i] = y_even[i] + w*y_odd[i];
        y[i+l/2] = y_even[i] - w*y_odd[i];
        w=w*wn;
    }
    return y;
    
}

 int nextPowerOf2(int n)  
{  
    int count = 0;
    if (n && !(n & (n - 1)))  
        return n;  
      
    while( n != 0)  
    {  
        n >>= 1;  
        count += 1;  
    }  
      
    return 1 << count;  
}  

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin>>n;
    for (int i=0;i<n;i++){
        int l;
        cin>>l;
        vector<complex<double>> A;
        for(int j=0;j<l;j++){
            double a,b;
            cin>>a>>b;
            A.push_back(complex<double>(a,b));
        }
        long nearest_pow_2 =nextPowerOf2(l) ;

        for(int k = l;k<nearest_pow_2;k++){
            A.push_back(complex<double>(0.0,0.0));
        }
        vector<complex<double>> ans1 ;
        ans1 = Recursive_FFT(A);
        
        for(int k = 0;k<ans1.size();k++){
            cout.setf(ios::fixed,ios::floatfield);
            cout.precision(3);
            cout<<ans1[k]<<endl;
        }
    }
    return 0;
}
