#include <stdio.h>

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

long long power(long long base, int exp) {
    if (exp == 0) {
        return 1;
    }
    return base * power(base, exp - 1);
}

int main(void) {
    long long x, y, g, lcm, pow_res;
    int exp;

    printf("Enter two positive integers: ");
    if (scanf("%lld %lld", &x, &y) != 2 || x <= 0 || y <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter exponent (non-negative) for first number: ");
    if (scanf("%d", &exp) != 1 || exp < 0) {
        printf("Invalid exponent.\n");
        return 1;
    }

    g = gcd(x, y);
    lcm = (x / g) * y;
    pow_res = power(x, exp);

    printf("GCD: %lld\n", g);
    printf("LCM: %lld\n", lcm);
    printf("%lld^%d: %lld\n", x, exp, pow_res);

    return 0;
}
