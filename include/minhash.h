#ifndef MINHASH_H_
#define MINHASH_H_

#include <unordered_set>
#include <string>
#include <vector>
#include <map>

struct HashFunction
{
    int a = 0, b = 0, c = 0;

    HashFunction()
    {
    }

    HashFunction(int a, int b, int c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

class MinHash
{
private:
    const int Sketch_Size = 10;//100;
    const int Highest_Prime = 2147483647;
    const int Seed = 42;
    std::map<std::string, std::vector<unsigned int>> history;

    unsigned int compute_hash(const std::string &shingle, const HashFunction &hashFunction);
    std::vector<unsigned int> get_min_hash(const std::unordered_set<std::string> &shingles, std::vector<HashFunction>& hashFunctions);
    float get_jaccard_index(const std::vector<unsigned int> &minhashA, const std::vector<unsigned int> &minhashB);

public:
    float get_similarity(const std::string setA_name, const std::unordered_set<std::string> &setA, const std::string setB_name, const std::unordered_set<std::string> &setB);
};

#endif /*MINHASH_H_*/
