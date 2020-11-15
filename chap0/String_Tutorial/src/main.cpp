#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    string s1;
    string s2 = "hello";
    string s3 = s1;

    cin >> s1;

    string s4 = s2 + " " + s1;
    
    cout << s4 << endl;

    // Print every charecter in s4
    for(auto c : s4)
    {
        cout << c << ' ';
    }
    cout << endl;

    cin.ignore(256, '\n');

    cout << "Type: " << endl;
    string s5;
    getline(cin, s5);
    cout << s5 << endl; 
    if(!s5.empty()) 
    {
        cout << "s5 not empty." << endl;
    }
    if(s5.size() > 20)
    {
        cout << "s5 over Size" << endl;
    }

    return 0;   
}