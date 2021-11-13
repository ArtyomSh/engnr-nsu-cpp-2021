#include "hashFunctions.h"
#include <iostream>
#include <fstream>

void adler32(std::ifstream &file){
    uint32_t a = 1, b = 0;
    unsigned char s;
    while (file.read((char *)(&s), sizeof(unsigned char))) {
        a = (a + s) % 65521;
        b = (b + a) % 65521;
    }
    std::cout << std::hex << ((b << 16) | a) << std::endl;
}

void sum64(std::ifstream &file){
    uint64_t contr_sum = 0;
    while (!file.eof()) {
        uint64_t block = 0;
        file.read((char *) &block, sizeof(uint64_t));
        block = (((uint64_t)ntohl((block) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t)((block) >> 32));
        if (file.gcount() != 8){
            block >>= 64-8*file.gcount();
        }
        contr_sum += block;
    }
    std::cout << std::hex << contr_sum << std::endl;
}



