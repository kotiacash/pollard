#include <iostream>
#include <cmath>
#include <random>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

long long pollard_rho(long long n) {
  if (n <= 1) {
    return n;
  }
  if (n % 2 == 0) {
    return 2;
  }
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distrib(2, n - 1);
  long long x = distrib(gen);
  long long y = x;
  long long c = distrib(gen);
  long long d = 1;
  while (d == 1) {
    x = (x * x + c) % n;
    y = (y * y + c) % n;
    y = (y * y + c) % n;
    d = gcd(abs(x - y), n);
  }
  return d;
}

vector<long long> factorize(long long n) {
  vector<long long> factors;
  while (n > 1) {
    long long factor = pollard_rho(n);
    factors.push_back(factor);
    n /= factor;
  }
  return factors;
}

int main() {
  long long n;
  cout << "Enter a number to factorize: ";
  cin >> n;
  vector<long long> factors = factorize(n);
  cout << "The prime factorization of " << n << " is: ";
  for (int i = 0; i < factors.size(); i++) {
    cout << factors[i];
    if (i < factors.size() - 1) {
      cout << " * ";
    }
  }
  cout << endl;
  return 0;
}
