#include <vector>
#include <set>
#include <random>
#include <functional>
#include <bits/stdc++.h>
#include <minhash.h>

unsigned int MinHash::compute_hash(const std::string &shingle, const HashFunction &hashFunction)
{
    unsigned int hashValue = std::hash<std::string>{}(shingle);
    hashValue = (hashFunction.a * hashValue + hashFunction.b) % Highest_Prime;
    return hashValue;
}

// Calculate the minhash signatures for a set of shingles
std::vector<unsigned int> MinHash::get_min_hash(const std::unordered_set<std::string> &shingles, std::vector<HashFunction> &hashFunctions)
{
    std::vector<unsigned int> signatures(this->Sketch_Size, UINT_MAX);
    for (const std::string &shingle : shingles)
        for (int sketch_index = 0; sketch_index < Sketch_Size; ++sketch_index)
        {
            unsigned int new_hash = compute_hash(shingle, hashFunctions[sketch_index]);
            signatures[sketch_index] = std::min(signatures[sketch_index], new_hash);
        }
    return signatures;
}

// Calcuate the Jaccard Similarity Approximation
float MinHash::get_jaccard_index(const std::vector<unsigned int> &minhashA, const std::vector<unsigned int> &minhashB)
{
    int matchingSignatures = 0;
    for (int i = 0; i < this->Sketch_Size; ++i)
        if (minhashA[i] == minhashB[i])
            matchingSignatures++;

    return static_cast<float>(matchingSignatures) / Sketch_Size;
}

float MinHash::get_similarity(const std::string setA_name, const std::unordered_set<std::string> &setA, const std::string setB_name, const std::unordered_set<std::string> &setB)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    generator.seed(this->Seed);

    int universal_set_size = this->Highest_Prime -1 ;// std::max(setA.size(), setB.size());

    std::uniform_int_distribution<int> distribute(1, universal_set_size);

    // generate hash functions
    std::vector<HashFunction> hashFunctions(this->Sketch_Size);
    for (int i = 0; i < this->Sketch_Size; ++i)
        hashFunctions[i] = HashFunction(distribute(generator), distribute(generator), this->Highest_Prime);

    // create minhash signatures
    std::vector<unsigned int> minhashA, minhashB;
    if(this->history.find(setA_name) != this->history.end())
    {
        minhashA = this->history[setA_name];
    }
    else
    {
        minhashA = this->get_min_hash(setA, hashFunctions);
        this->history[setA_name] = minhashA;
    }

    if(this->history.find(setB_name) != this->history.end())
    {
        minhashB = this->history[setB_name];
    }
    else
    {
        minhashB = this->get_min_hash(setB, hashFunctions);
        this->history[setB_name] = minhashB;
    }

    // calculate jaccard similarity
    return this->get_jaccard_index(minhashA, minhashB);
}