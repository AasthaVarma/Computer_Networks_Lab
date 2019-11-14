#include<bits/stdc++.h>
using namespace std;

// returns xor of a and b(both of same length)
string xor_k_bits(string a, string b)
{
    string r = "";
    for(int i=0; i<a.length(); i++)
    {
        if(a[i]==b[i])
            r.append("0");
        else
            r.append("1");
    } 
    return r;
}
// returns d%k and performs modulo 2 division
string mod2div(string d, string k,int val)
{  
    string rem = "";
    string a = "";
    for(int i=0; i<k.length()-1; i++)
        a.append("0");
    if(val==0)
    d.append(a);
    int n= d.length(), klen = k.length();
    int i=0;
    //cout << "d: " << d << "\n";
    while(d[i]=='0')
            i++;
    string t = d.substr(i, klen);
    //cout << "t, k: " << t << " " << k << "\n";
    i = i+klen;
    int flag=0, j=0;
    while(i<n)
    {
        t = xor_k_bits(t, k);
        //cout << i << " " << t << "\n";
       
        while(t[j]=='0')
        {
            t.erase(0, 1);
            //cout << "0 erased: " << t << "\n";
            t.push_back(d[i]);
            //cout << "t char pushed: " << t << "\n";
            i++;
            flag=1;
        }
        if(flag)
        {
            //cout << "q: " << i << " " << t << "\n";
            flag=0;
        }
        else
        i++;
    }
    t = xor_k_bits(t, k);
    t.erase(0, 1);
    return t;
}
// returns 
string encode(string d, string k)
{
    string e = "";
    string temp = mod2div(d, k, 0);
    e.append(d);
    e.append(temp);
    return e;
}
// returns true if  string has all zeroes else false.
bool check(string a)
{
    for(int i=0; i<a.length(); i++)
        if(a[i]=='1')
            return false;
    return true;
}

int main()
{
	
    srand(time(NULL));
    string d = "100100";
    
    string k = "1101";
    string e="";
    e.append(encode(d, k));
    
    cout << "Data word to be sent: " << d << "\n";
    cout << "Key: " << k << "\n";
    
    
	cout << "Sender side:\nCode word sent: " << e << "\n"; 
	//let there be an error at random position
    e[rand()%d.length()] = 1-(e[rand()%d.length()]-'0') + '0';
    cout << "Code word received e: " << e << "\n";
    
    string ans = mod2div(e, k, 1);
    //ans is Remainder i.e., e%k 
    cout << ans << "\n";
    if(check(ans))
        cout << "No errors!";
    else
        cout << "Error(/s)!";
    return 0;
}
