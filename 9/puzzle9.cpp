#include <iostream>
#include <string>
#include "../helper.h"
#include <gmp.h>
#include <assert.h>

// gmp usage based on: https://home.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html

void readInput(mpz_t& result) {
    mpz_set_ui(result, 1);
    auto lambda = [&](const std::string& line){
        mpz_t n;
        int flag;
        mpz_init(n);
        flag = mpz_set_str(n, line.c_str(), 10);
        assert (flag == 0);
        mpz_mul(result, result, n);
        mpz_clear(n);
    };
    readInputFile(lambda);
}

int main() {
    mpz_t result;
    mpz_init(result);
    readInput(result);
    mpz_out_str(stdout, 10, result);
    std::cout << std::endl;
    mpz_clear(result);
    return 0;
}
