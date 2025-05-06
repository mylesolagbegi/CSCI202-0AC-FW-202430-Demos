
   #include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_set>
#include <string>
#include <cmath>
#include <vector>
#include <functional>
#include <random>
#include "person.h"

const int HT_SIZE = 10007;

// lecture activity implement universal hashing (number 6) from https://www.geeksforgeeks.org/hash-functions-and-list-types-of-hash-functions/
// rerun both experiments
// submit the clustered and uniform distribution results
const bool CLUSTERED = false;

void setup();
int universalHash(int key, int a, int b, int p, int m);
int hashing_midsquare(long key, int size);

int main()
{
    setup();
    std::ifstream in("exp.txt");
    int ht[HT_SIZE];
    int collisions = 0;
    int count = 0;
    unsigned long probeCount = 0;

    for (int i = 0; i < HT_SIZE; i++)
    {
        ht[i] = -1;
    }

    // Set up universal hash parameters
    std::default_random_engine gen(std::random_device{}());
    int p = 10000019;
    std::uniform_int_distribution<int> randA(1, p - 1);
    std::uniform_int_distribution<int> randB(0, p - 1);
    int a = randA(gen);
    int b = randB(gen);

    while (!in.eof())
    {
        int num;
        in >> num;
        if (!in)
        {
            break;
        }

        int hashValue = universalHash(num, a, b, p, HT_SIZE);

        if (ht[hashValue] == -1)
        {
            ht[hashValue] = num;
            std::cout << num << " inserted at " << hashValue << std::endl;
            count++;
        }
        else
        {
            std::cout << num << " collided with " << ht[hashValue] << std::endl;
            collisions++;
            bool found = false;
            int pCount = 0;
            int i = 1;
            while (ht[hashValue] != -1 && !found && pCount < HT_SIZE / 2)
            {
                if (ht[hashValue] == num)
                {
                    found = true;
                }
                else
                {
                    hashValue = (hashValue + i * i) % HT_SIZE;
                    probeCount++;
                    pCount++;
                    i++;
                }
            }

            if (found)
            {
                collisions--;
                probeCount -= pCount;
                std::cout << "Duplicates are not allowed" << std::endl;
            }
            else if (pCount >= HT_SIZE / 2)
            {
                std::cout << "The table is full." << std::endl;
                break;
            }
            else
            {
                ht[hashValue] = num;
                count++;
            }
        }
    }

    in.close();
    std::cout << (CLUSTERED ? "\n[CLUSTERED]" : "\n[UNIFORM]") << std::endl;
    std::cout << "There were " << collisions << " collisions." << std::endl;
    std::cout << "There were " << count << " items inserted." << std::endl;
    std::cout << "There were " << static_cast<double>(probeCount) / collisions
              << " average probes per collision." << std::endl;

    // Sample Person usage
    Person **people = new Person *[13];
    Person james("james", 28);
    Person semaj("semaj", 28);
    int jamesHash = james.hash() % 13;
    int semajHash = semaj.hash() % 13;
    people[jamesHash] = &james;
    people[semajHash] = &semaj;

    delete[] people;
    return 0;
}

void setup()
{
    std::ofstream out("exp.txt");
    std::unordered_set<int> randomData;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> clusteredDist(100000, 100999);
    std::uniform_int_distribution<int> uniformDist(100000, 999999);

    while (randomData.size() < 5000)
    {
        int num = CLUSTERED ? clusteredDist(generator) : uniformDist(generator);
        randomData.insert(num);
    }

    for (int i : randomData)
    {
        out << i << std::endl;
    }

    out.close();
}

int universalHash(int key, int a, int b, int p, int m)
{
    return ((a * key + b) % p) % m;
}

int hashing_midsquare(long key, int size)
{
    int squareLen = 0;
    int mid_pos = 0;
    unsigned long keysquare = key * key;
    std::string squaredStr = std::to_string(keysquare);
    squareLen = squaredStr.length();
    if (squareLen < size)
    {
        squaredStr = std::string(size - squareLen, '0') + squaredStr;
        squareLen = size;
    }
    mid_pos = (squareLen - size) / 2;
    std::string midDigits = squaredStr.substr(mid_pos, size);
    return std::stoi(midDigits) % HT_SIZE;
}

}
