#include "TSTNode.hpp"
#include <stdio.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

class TST {
public:
  TSTNode * root = 0;

  TST(const vector<string> words){
    //cout << "begin constructor" << endl;
      for(unsigned int index = 0; index < words.size(); ++index){
        insert(words[index]);
      }
  }

  ~TST(){
    deleteTrie(root);
  }

  void deleteTrie(TSTNode * curr){
    if(curr->left){
      deleteTrie(curr->left);
    }
    if(curr->right){
      deleteTrie(curr->right);
    }
    if(curr->mid){
      deleteTrie(curr->mid);
    }
   
    delete(curr);
  }
/*
  string printString(TSTNode * endNode){
    TSTNode * curr = endNode;
    if(!(endNode->endWord)){
      return 0;
    }

    string result = "";
    result += curr->data;

    while(curr->parent){
      curr = curr->parent;

      if(!curr->isMidChild){
        if(curr->parent){
          curr = curr->parent;
          result += curr->data;
        }
        else{
          break;
        }
      }
      else{
        result += curr->data;
      }
    }
    return result;
  }
*/
  void insert(string word){
    unsigned int letter = 0;
    if(root == 0){
      //cout << "root initializing" << endl;
      root = new TSTNode(word[0]);
      //cout << root->data << endl;
    }
    TSTNode * curr = root;
    
    while(letter < word.length()){
      if(word[letter] < curr->data){
        if(curr->left){
          curr = curr->left;
        }
        else{
          //++letter;

          if(letter < word.length()){
            curr->left = new TSTNode(word[letter]);
            curr = curr->left;
            ++letter;
          }

          while(letter < word.length()){
            curr->mid = new TSTNode(word[letter]);
            curr = curr->mid;
            ++letter;
          }
          curr->endWord = 1;
          ++curr->frequency;
          curr->myWord = word;
          break;
        }
      }
      else if(word[letter] > curr->data){
        //cout << "within right else" << endl;
        if(curr->right){
          curr = curr->right;

        }
        else{
          //++letter;

          if(letter < word.length()){
            curr->right = new TSTNode(word[letter]);
            //cout << curr->right->data << endl;
            curr = curr->right;
            ++letter;
          }

          while(letter < word.length()){
            curr->mid = new TSTNode(word[letter]);
            //cout << curr->mid->data << endl;
            curr = curr->mid;
            ++letter;
          }
          curr->endWord = 1;
          ++(curr->frequency);
          curr->myWord = word;
          break;
        }
      }
      else{
        //cout << "within mid else" << endl;
        if(curr->mid){
          ++letter;
          if(letter >= word.length()){
            curr->endWord = 1;
            ++(curr->frequency);
            curr->myWord = word;
            break;
          }
          curr = curr->mid;
        }
        else{
          ++letter;
          while(letter < word.length()){
            curr->mid = new TSTNode(word[letter]);
            //cout << curr->mid->data << endl;
            curr = curr->mid;
            ++letter;
          }
          curr->endWord = 1;
          ++(curr->frequency);
          curr->myWord = word;
          break;
        }
      }
    }
  }

};
