/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include "bloom.h"
 #include <functional> 
 #include <vector>
#include <random>
#include <algorithm>
#include <ctime>

BF::BF(uint64_t size, std::vector<hashFunction> hashList){

hv = hashList;

bv.resize(size);
for(unsigned int i = 0 ; i < bv.size(); i++){
    bv[i] = false;
    }
 
}

BF::BF(const BF& other){
    // Your code here
 
    hv = other.hv;
    bv = other.bv;

}

BF::~BF(){

}

void BF::add(const int & key){

for (unsigned long i = 0; i < hv.size() ; i++){
    auto &func = hv[i];
    u_int64_t position = func(key) % bv.size();    
    bv[position] = true;
    }
}


bool BF::contains(const int& key) const{
    // Your code here 
for (unsigned long i = 0; i < hv.size() ; i++){
    auto &func = hv[i];
    u_int64_t position = func(key) % bv.size();    
    if(!bv[position]) {
        return false;
    }
    }
    return true;
}

void BF::bit_union(const BF& other){
for (unsigned long i = 0; i < bv.size(); ++i) {
        bv[i] = (bv[i] || other.bv[i]);  // OR
    }
}


void BF::intersect(const BF& other){
  for (unsigned long i = 0; i < bv.size(); ++i) {
        bv[i] = (bv[i] && other.bv[i]);  // AND
    }
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){


  BF bloomFilter(size, hashList);

    for (int num : inList) {
        bloomFilter.add(num);
    }

   int FalsePos = 0;
    int Negative = 0;
    for (size_t i = 0; i < max; i++){
        auto it = std::find(inList.begin(), inList.end(), i);
        if (bloomFilter.contains(i) && (it ==inList.end())){
            FalsePos++;
        }
        else if (!bloomFilter.contains(i) && (it ==inList.end())){
            Negative++;
        }
    }

   return ((float)(FalsePos)) / ((float)(FalsePos + Negative));
   }


bool getBitFromArray(std::vector<char> bv, int index){
 int byteIndex = index / 8;    
int bitIndex = index % 8; 

 char bit = bv[byteIndex] & (1 << (7 - bitIndex));
 return bit != 0;
}

bool getBitFromByte(char in, int index){
    char bit = in & (1 << (7 - index));

    return bit != 0;

}

