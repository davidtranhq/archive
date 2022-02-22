/*
Description

5 Friends (let's call them a, b, c, d and e) are playing a game and need to keep track of the scores. Each time someone scores a point, the letter of his name is typed in lowercase. If someone loses a point, the letter of his name is typed in uppercase. Give the resulting score from highest to lowest.
Input Description

A series of characters indicating who scored a point. Examples:

abcde
dbbaCEDbdAacCEAadcB

Output Description

The score of every player, sorted from highest to lowest. Examples:

a:1, b:1, c:1, d:1, e:1
b:2, d:2, a:1, c:0, e:-2

Challenge Input

EbAAdbBEaBaaBBdAccbeebaec

Credit

This challenge was suggested by user u/TheMsDosNerd, many thanks! If you have any challenge ideas, please share them in r/dailyprogrammer_ideas and there's a good chance we'll use them.

https://www.reddit.com/r/dailyprogrammer/comments/8jcffg/20180514_challenge_361_easy_tally_program/

*/
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>
#include <vector>

std::vector<std::pair<char, int>> sort_scores(std::map<char, int> scores)
{
    // store scores in vector to sort
    std::vector<std::pair<char, int>> sorted;
    for (auto p : scores)
        sorted.push_back(p);
    // comparator lambda in descending order
    auto cmp = [](std::pair<char, int> a, std::pair<char, int> b)
               { return a.second > b.second; };
    // sort
    std::sort(sorted.begin(), sorted.end(), cmp);
    return sorted;
}

int main(void)
{
    // input
    std::string t;
    std::cin >> t;
    
    // parse input
    std::map<char, int> scores;
    for (char c : t)
    {
        if (islower(c))
            scores[c] += 1; // lower-case adds a point
        else
            scores[tolower(c)] -= 1; // upper-case removes one
    }
    
    // sort scores
    std::vector<std::pair<char, int>> sorted = sort_scores(scores);
    
    // output
    for (auto p : sorted)
        std::cout << p.first << ':' << p.second << ' ';
    return 0;
}