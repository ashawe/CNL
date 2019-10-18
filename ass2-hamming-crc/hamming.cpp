#include<iostream>
#include<vector>
#include<algorithm>
#include <sstream> 
#include<cmath>
using namespace std;

int binaryToDecimal(string n) 
{ 
    string num = n; 
    int dec_value = 0; 
  
    // Initializing base value to 1, i.e 2^0 
    int base = 1; 
  
    int len = num.length(); 
    for (int i = len - 1; i >= 0; i--) { 
        if (num[i] == '1') 
            dec_value += base; 
        base = base * 2; 
    } 
  
    return dec_value; 
} 


bool isPowerOfTwo(int n) 
{ 
   if(n==0) 
   return false;
   return (ceil(log2(n)) == floor(log2(n))); 
} 

string toBinary( int x ){
    string b;
    if(x==0) return "0";
    while(x!=0)
    {
        b = (x%2==0?"0":"1") + b;
        x = x / 2; 
    }
    return b;
}

int getR(int len)
{
    int r = 0;
    while( pow(2,r) < (len+r+1) )
        r++;
    return r;
}


// returns decimal of single digit char
int testnum(char c)
{
    switch(c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2' :
            return 2;
        case '3' :
            return 3;
        case '4' :
            return 4;
        case '5' :
            return 5;
        case '6' :
            return 6;
        case '7' :
            return 7;
        case '8' :
            return 8;
        case '9' :
            return 9;
    }
}


// returns vector of redundant bits
vector<int> hammingBits (string input, int r,bool rev)
{
    vector<int> bits;
    string ip = input;
    int ipLen = input.length();
    int totalLen = ipLen;
    if(!rev)
        totalLen =  ipLen + r;

    // at which place from right we want 1
        // for ex. for R1 we want '1' at the LSB
    for( int i = 0; i < r; i++ )    
    {
        //  cout << "R" << i;
        int count = 0,bit;
        // iterate through ip and find AND of only bits which have '1' at appropriate place
        for( int j = 1; j <= totalLen; j++)
        {
            string bin = toBinary(j);
            int len = bin.length();

            if( bin[len-i-1] == '1' )
            {
                if( ip[ ( (j-1) ) ] == '1' )
                    count++;

            }
        }

        bit = (count%2);
        bits.push_back(bit);

    }
    return bits;

}

// returns m+r len hamming code
string usingBinary(string ip){
    int ipLen = ip.length();
    int r = getR(ipLen);

    int totalLen = ipLen+r;
    int code[totalLen];
    int counter = 0;

    // demo hamming code with 0 in place of redundant bits;
    for(int i = 0; i < totalLen; i++ )
    {
        if( isPowerOfTwo(i+1) )
        {
            code[i] = 0;
        }
        else
        {
            code[i] = testnum(ip[ipLen-counter-1]);
            counter++;
        }
    }

    string codeStr;
    for( int i : code )
    {
        codeStr += i==1? '1' : '0';
    }

    vector<int> bits;
    bits = hammingBits(codeStr,r,true);

    int cnt = 1;
    for(int i = 0; i < r; i++)
    {
        code[cnt-1] = bits[i];
        bits.pop_back();
        cnt*=2;
    }

    // converting full m + r len code to string
    string res;
    for(int i = 0; i < totalLen; i++ )
    {
        res += code[i] == 1 ? '1' : '0';
    }
    return res;
}

// generates error bits on reciever side
int errorBits(string input)
{
    int r = getR(input.length());
    vector<int> bits;
    bits = hammingBits(input,r,true);

    // creating string from error bits
    string x;
    for(int i : bits)
       x += i == 1 ? '1' : '0';

    // reversing error ( nessesary )
    string rev = x;
    int ctr = 0;
    for( int i = x.length()-1; i>=0; i--)
    {
        rev[ctr] = x[i];
        ctr++;
    }

    return binaryToDecimal(rev);
}

int main()
{
    string input;
    int change;
    cout << "Enter 8 bit binary number\n";
    cin >> input;
    string hamming = usingBinary(input);
    int hamLen = hamming.length();
    cout << "Created Hamming Code: " << hamming << endl;
    cout << "Which bit to change? ( 0 if not to change)";
    cin >> change;
    if( change!= 0 && change < hamming.length() )
    {
        hamming[change-1] = hamming[change-1] == '1' ? '0' : '1';
    }
    cout << "new number:" << hamming << endl;
    int err = errorBits(hamming);
    // cout << "ERR:" <<err << endl;
    if( err < hamming.length() && err != 0)
        cout << "Error is at: " << err << " Position";
    else
        cout << "No Error";
    return 0;
}
// 1011001