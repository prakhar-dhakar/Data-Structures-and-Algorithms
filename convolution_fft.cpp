#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <complex>
#include <vector>

using namespace std;

vector<complex<long double>> Recursive_FFT(vector<complex<long double>> A){
    int l = A.size();
    if(l==1){
        // cout<<A[0]<<"he";
        return A;
    }
    long double alpha = 2*M_PI/l;
    complex<long double> w(1,0) , wn(cos(alpha),sin(alpha));
    vector<complex<long double>> even(l/2);
    vector<complex<long double>> odd(l/2);
    for (int i=0;i<l/2;i++){
        even[i] = A[2*i];
        odd[i] = A[2*i+1];
    }
    vector<complex<long double>> y_even =Recursive_FFT(even);;
    vector<complex<long double>> y_odd =Recursive_FFT(odd);
    vector<complex<long double>> y(l);
    for (int i=0;i< l/2 ;i++){
        y[i] = y_even[i] + w*y_odd[i];
        y[i+l/2] = y_even[i] - w*y_odd[i];
        w=w*wn;
    }
    return y;
    
}
vector<complex<long double>> InverseFFT(vector<complex<long double>> A){
    int l = A.size();
    if(l==1){
        // cout<<A[0]<<"he";
        return A;
    }
    long double alpha = 2*M_PI/l;
    complex<long double> w(1,0) , wn(cos(alpha),sin(-alpha));
    vector<complex<long double>> even(l/2);
    vector<complex<long double>> odd(l/2);
    for (int i=0;i<l/2;i++){
        even[i] = A[2*i];
        odd[i] = A[2*i+1];
    }
    vector<complex<long double>> y_even =InverseFFT(even);;
    vector<complex<long double>> y_odd =InverseFFT(odd);
    vector<complex<long double>> y(l);
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
        vector<complex<long double>> A,B;
        for(int j=0;j<l;j++){
            long double a,b;
            cin>>a>>b;
            A.push_back(complex<long double>(a,b));
        }
        for(int j=0;j<l;j++){
            long double a,b;
            cin>>a>>b;
            B.push_back(complex<long double>(a,b));
        }
        long nearest_pow_2 =nextPowerOf2(2*l) ;

        for(int k = l;k<(nearest_pow_2);k++){
            A.push_back(complex<long double>(0.0,0.0));
            B.push_back(complex<long double>(0.0,0.0));
        }
        vector<complex<long double>> fft_A,fft_B, ab(nearest_pow_2),ans ;
        fft_A = Recursive_FFT(A);
        fft_B = Recursive_FFT(B);
        for (int i=0;i<fft_A.size();i++){
            ab[i] = fft_A[i] * fft_B[i];
        }
        
        ans = InverseFFT(ab);
        
        
        for(int k = 0;k<ans.size();k++){
            cout.setf(ios::fixed,ios::floatfield);
            long double limit = 0.001;
            long double temp1 = real(ans[k])/ans.size();
            long double temp2 = imag(ans[k])/ans.size();
            if(fabs(temp1)<limit)temp1 = 0.000;
            if(fabs(temp2)<limit)temp2 = 0.000;
            ans[k]= complex<long double>(temp1,temp2);
            cout.precision(3);
            cout<<ans[k]<<endl;
        }
    }
    return 0;
}
