#include <climits>
#include "../include/big_int.hpp"

// 2 ^ 3 mod 3
// 8 mod 3
// 2
// 2 % 3 = 2
// 3 / 2 = 1

// 3 ^ 2 mod 4
// 3 ^ 1 mod 4
BigInt mod_exp(const BigInt& base, const BigInt& exp, const BigInt& mod){
    if (exp < BigInt(0) or mod< BigInt(0)){
        throw std::invalid_argument("Division by zero");
    }
    if (exp == BigInt(0)) {
        return BigInt{1};
    }
    BigInt a = mod_exp(base % mod, exp / BigInt(2), mod) % mod;
    if (exp.is_even()){
        return (a * a) % mod;
    } else {
        return ((base % mod) * ((a * a) % mod)) % mod;
    }
}
