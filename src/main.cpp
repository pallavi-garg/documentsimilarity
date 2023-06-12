#include <iostream>
#include <string>
#include <minhash.h>
#include <brute_force.h>
#include <chrono>
#include <unordered_set>
#include <fstream>
#include <bits/stdc++.h>
#include <map>

typedef std::chrono::time_point<std::chrono::system_clock> time_type;

std::map<std::string, std::unordered_set<std::string>> history_shingles;

std::unordered_set<std::string> get_shingles(std::string &file, int shingle_size)
{
    if (history_shingles.find(file) != history_shingles.end())
    {
        return history_shingles[file];
    }
    else
    {
        std::unordered_set<std::string> shingles_set = std::unordered_set<std::string>();
        std::ifstream inputFile(file);
        if (inputFile.is_open())
        {
            std::string line = "";
            while (getline(inputFile, line))
            {
                line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                int len = (int)line.length() - shingle_size;
                for (int i = 0; i <= len; ++i)
                {
                    std::string str = line.substr(i, shingle_size);
                    while ((int)str.length() != shingle_size)
                        str += " ";
                    shingles_set.insert(str);
                }
            }
            inputFile.close();
        }
        return shingles_set;
    }
}

int main()
{
    int shingle_size = 8;

    MinHash *minhash = new MinHash();
    Brute_Jaccard *brute_jaccard = new Brute_Jaccard();

    for (int i = 1; i < 2; ++i)
    {
        for (int j = 1; j < 13; ++j)
            if (i != j)
            {
                std::string fileA = "test/set" + std::to_string(i) + ".txt";
                auto setA = get_shingles(fileA, shingle_size);
                std::string fileB = "test/set" + std::to_string(j) + ".txt";
                auto setB = get_shingles(fileB, shingle_size);

                time_type start_time = std::chrono::system_clock::now();
                float minhash_result = minhash->get_similarity(fileA, setA, fileB, setB);
                time_type now_time = std::chrono::system_clock::now();
                std::chrono::duration<double> minhash_elapsed_seconds = now_time - start_time;

                start_time = std::chrono::system_clock::now();
                float brute_result = brute_jaccard->get_similarity(setA, setB);
                now_time = std::chrono::system_clock::now();
                std::chrono::duration<double> brute_elapsed_seconds = now_time - start_time;

                std::cout << "Time taken by minhash for " << fileA << " (set size " << setA.size() << ") and " << fileB << " (set size " << setB.size() << ") is: " << minhash_elapsed_seconds.count() * 1000 << "ms and similarity is " << minhash_result << std::endl;
                std::cout << "Time taken by brute force for " << fileA << " (set size " << setA.size() << ") and " << fileB << " (set size " << setB.size() << ") is: " << brute_elapsed_seconds.count() * 1000 << "ms and similarity is " << brute_result << std::endl;
                std::cout << std::endl
                          << std::endl;
            }
    }
    delete minhash;
    delete brute_jaccard;

    return 0;
}