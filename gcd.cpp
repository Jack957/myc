#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    return b ? gcd(b, a%b) : a;
}
int main() {
    int n1, n2;
    cout << "Enter two numbers: ";
    cin >> n1 >> n2;


    cout << "GCD = " << gcd(n1, n2) << endl;
    return 0;
}
