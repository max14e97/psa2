/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Author: Jonathan Margoliash
 *  Modified from code authored by: Jor-el Briones, Christine Alvarado
 */

#ifndef AUTOCOMPLETE_HPP
#define AUTOCOMPLETE_HPP

#include "TSTNode.hpp"
#include "TST.hpp"
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;


bool sortFunc(const pair<int, string> &p1, const pair<int, string> &p2) {
  if(p1.first != p2.first){
    return p1.first > p2.first;
  }
  else{
    return p1.second < p2.second;
  }
}

/**
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie.
 */
class Autocomplete
{
public:

  /* 
  Create an Autocomplete object.
  This object should be trained on the words vector
  That is - the predictCompletions() function below should pull autocomplete
  suggestions from this vector

  Input: words. Must be all lowercase, with most  non-word characters removed (e.g. ',' ';' '%' etc.)
  In addition to alphabetic characters, words may contain digits, single apostrophes, dashes etc.
  */
  Autocomplete(const vector<string> words) {

    //cout << "inside Autocomplete constructor" << endl;
    if(words.size() != 0){
      trie = new TST(words);
    }
    //cout << "tree initialized" << endl;
  }
  /* Return up to 10 of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than 10 legal completions, this
   * function returns a vector with as many completions as possible.
   * Otherwise, 10 completions should be returned.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the 10 most frequent completions
   * of the prefix)
   * If you need to choose between two or more completions which have the same frequency,
   * choose the one that comes first in alphabetical order.
   *
   * Inputs: prefix. The prefix to be completed. Must be of length >= 1.
   * Return: the vector of completions
   */
  vector<string> predictCompletions(const string prefix) {
    //cout << "inside predictCompletions" << endl;
    vector<string> returnString;
    
    if(trie == 0){
      return returnString;
    }

    //find the starting node of the prefix
    TSTNode * start = predictFind(prefix);

    if(start == 0){
      return returnString;
    }

/*
    if(!start){
      cout << "predictFind returns nothing" << endl;
    }
    cout << "predictFind node is " << start->data << endl;
*/
    vector<pair<int, string>> pairArr;
    if(start->endWord == 1){
      pairArr.push_back(make_pair(start->frequency, start->myWord));
      /*
      if(start == 0){
        returnString.push_back(pairArr[0].second);
      }*/
    }
if(start->mid){
    traversal(start->mid, &pairArr);
}
/*
    for(int index = 0; index < pairArr.size(); ++index){
      cout << index << "th element is " << pairArr[index].second << endl;
    }
*/
    sort(pairArr.begin(), pairArr.end(), sortFunc);

/*
    for(int index = 0; index < pairArr.size(); ++index){
      cout << index << "th element is " << pairArr[index].second << 
      " and frequency is " << pairArr[index].first << endl;
    }
*/
    int limit = pairArr.size();
    if(pairArr.size() > 10){
      limit = 10;
    }
    pairArr.resize(limit); //CORRECT

    //loop through vector, gets out node ptrs (pairArr[index].first)
    //sort them and take first 10. If tie, alphabetical order.
    /*
    vector<pair<string, int>> resultArr;
    int limit = pairArr.size();
    if(pairArr.size() > 10){
      limit = 10;
    }
    for(int index = 0; index < limit; ++index){
      resultArr.push_back(pairArr[index]);
    }
    */

    //TST::find to find strings
    for(unsigned int index = 0; index < pairArr.size(); ++index){
      //call find to find resultArr[index]->data string
      returnString.push_back(pairArr[index].second);
    }

    return returnString; //TODO
  }

  //pair
  void traversal(TSTNode * curr, vector<pair<int, string>> * pairArr){
    //cout << "inside traversal" << endl;
    if(curr->left){
      traversal(curr->left, pairArr);
    }

    if(curr->endWord){
      //cout << "inside traversal making pairs" << endl;
      pairArr->push_back(make_pair(curr->frequency, curr->myWord));
      //cout << "pair made and pushed" << endl;
    }
    
    if(curr->mid){
      traversal(curr->mid, pairArr);
    }
    if(curr->right){
      traversal(curr->right, pairArr);
    }
  }

  //Finds the node containing the last letter of the input string.
  TSTNode * predictFind(const string word) {
    unsigned int letter = 0;
    TSTNode * curr = trie->root;
    TSTNode * result = 0;
/*
    cout << "inside predictFind aaaaaaaaa" << endl;
    cout << "word length = " << word.length() << endl;
    if(!curr){
      cout << "no root" <<endl;
    }
    else{
      cout << "root has " << curr->data << endl;
    }
*/ 
     while(letter < word.length() && curr){
      //cout << "inside while" << endl;
      if(word[letter] < curr->data){
        if(curr->left){
          curr = curr->left;
        }
        else{
          return 0;
        }
      }
      else if(word[letter] > curr->data){
        if(curr->right){
          curr = curr->right;

        }
        else{
          return 0;
        }
      }
      else{
        //cout << "inside mid else" << endl;
        if(curr->mid){
          ++letter;
          //cout << "inside have mid child and letter= " << letter << endl;
          if(letter >= word.length()){
            result = curr;
            //cout << "returning " << result->data << endl;
            break;
          }
          //cout << "curr has " << curr->data << endl;
          curr = curr->mid;
        }
        else{
          ++letter;
	  if(letter >= word.length()){
            result = curr;
            //cout << "returning " << result->data << endl;
            break;
          }

          return 0;
        }
      }
    }   

    //cout << "returning " << result->data << endl;
    return result;
  }

  /* Destructor */
  ~Autocomplete() {
    delete(trie);
  }

  //You may add your own code here

private:

  //you may add your own code here
  TST * trie = 0;

};

#endif // AUTOCOMPLETE_HPP
