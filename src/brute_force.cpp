#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <brute_force.h>

using namespace std;

float Brute_Jaccard::get_similarity(const std::unordered_set<std::string> &setA, const std::unordered_set<std::string> &setB)
{
    std::unordered_set<std::string> intersectionSet;
    for (const auto &shingle : setA)
        if (setB.count(shingle) > 0)
            intersectionSet.insert(shingle);

    return static_cast<float>(intersectionSet.size()) / (setA.size() + setB.size() - intersectionSet.size());
}