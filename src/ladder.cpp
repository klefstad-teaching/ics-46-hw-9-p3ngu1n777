#include "ladder.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg){
    cerr << "Error: " << word1 << word2 << msg << endl;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d){
    return (compute_difference(str1, str2) <= d);
}

int compute_difference(const std::string& str1, const std::string& str2){
    if(str1.empty()){
        return str2.length();
    }
    if(str2.empty()){
        return str1.length();
    }
    if(str1[0] == str2[0]){
        return compute_difference(str1.substr(1), str2.substr(1));
    }

    int change = compute_difference(str1.substr(1), str2.substr(1));
    int add = compute_difference(str1.substr(1), str2);
    int dele = compute_difference(str1, str2.substr(1));
    return 1 + min({change, add, dele});
}

bool is_adjacent(const string& word1, const string& word2){
    if(word1 == word2){
        return false;
    }
    if(abs(int(word1.length()) - int(word2.length())) > 1){
        return false;
    }

    int diff_char = 0;
    int cur_word1 = 0;
    int cur_word2 = 0;

    while(cur_word1 < word1.length() && cur_word2 < word2.length()){
        if(word1[cur_word1] != word2[cur_word2]){
            diff_char = diff_char + 1;
            if(diff_char > 1){
                return false;
            }
            if(word1.length() > word2.length()){
                cur_word1 = cur_word1 + 1;
            }
            else if(word2.length() > word1.length()){
                cur_word2 = cur_word2 + 1;
            }
            else{
                cur_word1 = cur_word1 + 1;
                cur_word2 = cur_word2 + 1;
            }
        }
        else{
            cur_word1 = cur_word1 + 1;
            cur_word2 = cur_word2 + 1;
        }
    }

    if(cur_word1 < word1.length() || cur_word2 < word2.length()){
        diff_char = diff_char + 1;
    }
    return diff_char == 1;
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        string last_word = ladder.back();
        ladder_queue.pop();
        
        for(const string& word: word_list){
            if(is_adjacent(last_word, word)){
                if(visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == end_word){
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }

    return {};
}

void load_words(set<string> &word_list, const string &file_name){
    ifstream file(file_name);
    
    string cur_word;
    while(file >> cur_word){
        word_list.insert(cur_word);
    }
}

void print_word_ladder(const vector<string> &ladder){
    for(int i = 0; i < ladder.size(); i++){
        cout << ladder[i] << " ";
    }
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

