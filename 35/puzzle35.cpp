#include <iostream>
#include <string>
#include <unordered_set>
#include "../helper.h"

auto readInput() {
    std::string result;
    auto lambda = [&](const std::string& line) {
        result = line.substr(0, line.length() - 1);
    };
    readInputFile(lambda);
    return result;
}

auto readWords() {
    std::vector<std::string> result;
    auto lambda = [&](const std::string& line) {
        result.push_back(line.substr(0, line.length() - 1));
    };
    readInputFile(lambda, "words.txt");
    return result;
}

std::vector<std::pair<char, int>> findPermutation(const std::string& codeWord) {
    std::vector<std::pair<char, int>> result;
    for (int i = 0; i < codeWord.length(); i++) {
        result.push_back({ codeWord[i], i });
    }
    std::stable_sort(result.begin(), result.end());
    return result;
}

int main() {
    std::vector<std::string> englishWords = { 
        "the", "her", "him", "he", "she", 
        "we", "our", "you", "is", "am", 
        "has", "have", "had", "was", "can",
        "could", "would", "let", "that", "so",
        "me", "your", "they", "them", "it", 
        "what", "which", "who", "this", "did",
        "do", "and", "or", "not"
    };
    std::unordered_set<std::string> set;
    for (const auto& word : englishWords) {
        set.insert(word);
    }
    auto input = readInput();
    auto words = readWords();
    std::string clearText;
    clearText.resize(input.length());
    for (const auto& codeWord : words) {
        if (input.length() % codeWord.length() != 0)
            continue;
        int rowSize = codeWord.length();
        int columnSize = input.length() / codeWord.length();
        auto permutation = findPermutation(codeWord);
        for (int i = 0; i < rowSize; i++) {
            int permutated = permutation[i].second;
            for (int j = 0; j < columnSize; j++) {
                clearText[permutated + j * rowSize] = input[j + i * columnSize];
            }
        }
        auto parts = split(clearText, " ");
        int matches = 0;
        for (const auto& part : parts) {
            if (set.find(part) != set.end())
                matches++;
        }
        if (matches > 100) {
            //std::cout << clearText << std::endl;
            std::cout << codeWord << std::endl;
        }
    }
    return 0;
}
