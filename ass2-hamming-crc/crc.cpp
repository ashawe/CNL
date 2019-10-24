#include<iostream>
#include<deque>
#include<string.h>
#include<algorithm>
using namespace std;

deque<bool> getDeque(string input)
{
    deque<bool> result;
    int x = strlen(input.c_str());
    for (int i = 0; i < x; i++)
    {
        result.push_back( input[i] == '1'? 1:0 );
    }
    return result;
}

deque<bool> findCRC(string bin, string key, string CRC, bool isCheck)
{
    int binLen = strlen(bin.c_str());
    int keyLen = strlen(key.c_str());

    if(!isCheck)
        // Attaching ( key-1 ) number of 0's behind data word
        for( int i = 0; i < keyLen-1; i++ )
        {
            bin += '0';
        }
    else
    {
        // if checking CRC, concat crc instead of key
        for( int i = 0; i < keyLen; i++ )
        {
            bin += CRC[i];
        }
    }

    deque<bool> divisor = getDeque(key);
    deque<bool> divident = getDeque(bin);
    deque<bool> remainder;
    deque<bool> currentDivisor; // length of key; part of Divident which we want to xor
    string quotient;

    // copying ( key length ) part from divident for xor-ing with the key
    for (int i = 0; i < divisor.size()-1; i++)
    {
        currentDivisor.push_back(divident.front());
        divident.pop_front();
    }

    currentDivisor.push_back(divident.front());
    
    // Modulo 2
    while(! divident.empty() )
    {
        divident.pop_front();
        remainder.clear();
        if(currentDivisor.front() == 0)
        {
            quotient += '0';
            currentDivisor.push_back(divident.front());
            currentDivisor.pop_front();
            continue;
        }

        quotient += '1';
        for (int i = 0; i < divisor.size(); i++)
        {
            remainder.push_back( currentDivisor.front() ^ divisor[i] );
            currentDivisor.pop_front();
        }
        remainder.pop_front();        
        currentDivisor = remainder;
        currentDivisor.push_back(divident.front());
    }

    // if(!isCheck || quotient[quotient.length()-1] == '0')
    // {
    //     // for last digit
    //     quotient += '1';
    //     for (int i = 0; i < divisor.size(); i++)
    //     {
    //         remainder.push_back( currentDivisor.front() ^ divisor[i] );
    //         currentDivisor.pop_front();
    //     }
    //     remainder.pop_front();
    // }
    // cout << "Quotient: " << quotient << " CRC: ";
    cout << " CRC: ";
    for (int i = 0; i < remainder.size(); i++)
    {
        cout << remainder[i];
    }
    cout << endl;

    return remainder;
    
}


bool isValidCRC( deque<bool> CRC )
{
    for( int i : CRC )
        if( i != 0 )
            return false;
    return true;
}

// Data word to be sent - 100100
// Key - 1101

int main()
{
    string bin,key;
    int choice;

    cout << "Enter binary number\n";
    cin >> bin;
    int binLen = strlen(bin.c_str());
    cout << "Enter binary key\n";
    cin >> key;

    deque<bool> CRC = findCRC(bin,key,"",false);

    cout << "Enter bit to change ( 0 if no change ) ";
    cin >> choice;


    int totalLen = binLen+CRC.size();
    if( choice != 0 )
    {
        if( choice < binLen )
        {
            bin[choice-1] = bin[choice-1] == '1' ? '0' : '1';
        }
        else if ( choice <= (totalLen) )
        {
            CRC[choice-binLen-1] = !CRC[choice-binLen-1];
        }
    }
    string generatedCRC;

    for( int i : CRC )
    {
        generatedCRC+= i==1? '1':'0';
    }
    generatedCRC+='\0';

    if(!isValidCRC(findCRC(bin,key,generatedCRC,true)) )
        cout << "Error exists\n";
    else
        cout << "No Error\n";

    return 0;
}