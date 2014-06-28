#include <stdio.h>

long long Pow(long long a, long long n){
    long long ans = 1;

    while (n){
        if (n & 1){
            ans *= a;
        }
        a *= a;
        n >>= 1;
    }

    return ans;
}


int main()
{
    long long n;
    long long a;
    long long x;

    scanf("%lld %lld", &a, &n);

    x = Pow(a, n);

    printf("%lld", x);

    return 0;
}
