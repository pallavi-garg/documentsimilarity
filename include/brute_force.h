#ifndef Brute_H_
#define Brute_H_

#include <string>
#include <unordered_set>

class Brute_Jaccard
{
public:
    float get_similarity(const std::unordered_set<std::string> &setA, const std::unordered_set<std::string> &setB);
};

#endif /*Brute_H_*/
