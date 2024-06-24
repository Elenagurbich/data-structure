#include <iostream>
#include <tuple>

// Функция для вычисления gcd и коэффициентов x, y
std::tuple<long long, long long, long long> extended_gcd(long long a, long long b) {
    if (b == 0)
        return std::make_tuple(a, 1, 0);
    long long gcd, x1, y1;
    std::tie(gcd, x1, y1) = extended_gcd(b, a % b);
    long long x = y1;
    long long y = x1 - (a / b) * y1;
    return std::make_tuple(gcd, x, y);
}

// Функция для нахождения обратного элемента
long long mod_inverse(long long a, long long n) {
    long long gcd, x, y;
    std::tie(gcd, x, y) = extended_gcd(a, n);
    if (gcd != 1) {
        // Обратного элемента не существует
        return 0;
    } else {
        // Обратный элемент может быть отрицательным, поэтому приводим его к положительному значению
        return (x % n + n) % n;
    }
}

int main() {
    long long a, n;
    std::cin >> a >> n;

    long long result = mod_inverse(a, n);
    std::cout << result << std::endl;

    return 0;
}