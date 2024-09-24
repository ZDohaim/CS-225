/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

AnagramDict::AnagramDict(const string& filename) {
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            string key = word;
            std::sort(key.begin(), key.end()); // Sort to form the key
            dict[key].push_back(word);
        }
        wordsFile.close();
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words) {
    for (const string& word : words) {
        string key = word;
        std::sort(key.begin(), key.end()); // Sort to form the key
        dict[key].push_back(word);
    }
}
/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
  string key = word;
        std::sort(key.begin(), key.end());
        auto it = dict.find(key);
        if (it != dict.end()) {
            return it->second;
        }
        return {};
    }

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> res;

    for (const auto& [key, anags] : dict){
        if (anags.size() > 1){
            res.push_back(anags);
        }
    }
    return res;
}
