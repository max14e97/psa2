/**
 * CSE 100 PA2 SpeechBuilder
 * Author: Jonathan Margoliash
 */

#ifndef DOCUMENT_GENERATOR_HPP
#define DOCUMENT_GENERATOR_HPP

#include <string>
#include <dirent.h>
#include <unordered_map>
#include "AutocompleteUtils.hpp"

using namespace std;

typedef unordered_map<string, vector<pair<string, int>>> pairMap;

class DocumentGenerator
{
public:
  pairMap myMap;
  
 /**
 * Builds a document generator from the documents in the given directory
 * This should open all files in the directory, reads them in, tokenize them into words,
 * and build the datastructure from that stream of words.
 *
 * To tokenize a document:
 * * remove all UNWANTED_CHARACTERS from the document
 * * split it into different tokens based on whitespace
 *  (treat all whitespace breaks equally - newlines and spaces should be treated the same way)
 * * additionally split each PUNCTUATION character into its own token (so a single period is a 'word')
 *   (equivalently - treat all punctuation as if it was surrounded on both sides by a space)
 * * characters that are neither UNWANTED_CHARACTERS nor PUNCTUATION should be treated normally, the same way as any alphabetic character
 * * from here on, we'll use the word "word" to refer to both strings like "hello" and punctuation strings like "." or ","
 *
 * So, for instance, the short sentence
 * "I like trains. Sally ju^mped over the moon, I think? I. I think."
 * Would be tokenized into ["I", "like", "trains", ".", "Sally",
 *   "jumped", "over", "the", "moon", ",", "I", "think", "?", "I", ".", "I" "think", "."]
 * and the frequencies of the words after "I" would be;
 *  like - 1
 *  think - 2
 *  . - 1
 *
 * You may use the utilities in AutocompleteUtils to help you with this
 * and you may rely on them working.
 * Note however that they do not deal with unwanted characters or split punctuation appropriately.
 * 
 * A few notes:
 * 1) you must treat words with different capitalizatoins differently
 * * (so "foo" and "Foo" are different words, and the frequencies of the words that follow (or precede)
 * * "foo" will be different than the frequencies of the words that follow (or precede) "Foo" )
 * 2) pretend that the first word in each document is preceeded by a periood (That way, it is considered when starting any new sentence)
 */
  DocumentGenerator(const string documentsDirectory) {
    cout << "begin constructor" << endl;
    DIR * dir;
    struct dirent *ent;

    cout << "directory name is " << documentsDirectory.c_str() << endl;
    if((dir = opendir(documentsDirectory.c_str())) == NULL){
      cout << "opendir is null" << endl;
    }

    if((dir = opendir(documentsDirectory.c_str())) != NULL){
      while((ent = readdir(dir)) != NULL){
        cout << "my d name is " << ent->d_name << endl;

        vector<string> words = AutocompleteUtils::getWords(documentsDirectory + "/" + ent->d_name);

        if(words.size() == 0){
          continue;
        }

        for(int index = 0; index < words.size(); ++index){
          for(int j = 0; j < words[index].length(); ++j){
            for(int z = 0; z < UNWANTED_CHARACTERS.length(); ++z){
              if(words[index][j] == UNWANTED_CHARACTERS[z]){
                words[index].erase(j);
                //cout << "After WORD is: " << words[index] << endl;
                --j;
                break;
              }
            }
            for(int z = 0; z < PUNCTUATION.length(); ++z){
              if(words[index][j] == PUNCTUATION[z]){
                //cout << "Found a punctuation: " << string(words[index]) << endl;
                //index?
                string punc(1, words[index][j]);
                //cout << "My PUNCTUATION is " << punc << endl;
                words.insert(words.begin()+(index+1), punc);
                words[index].erase(j);
                //cout << "After word is: " << words[index] << " and punc is: " << words[index+1] << endl;
                --j;
                ++index;
                break;
              }
            }
          }
        }
        
/*
        for(int index = 0; index < words.size(); ++index){
          cout << words[index] << endl;
        }
*/

        //PROBLEM OF INDEX+1
        for(int index = 0; index < words.size()-1; ++index){
          if((myMap.count(words[index])) != 0){
            //check if the following word is in the vector or not;
            bool present = 0;
            for(int j = 0; j < myMap[words[index]].size(); ++j){
              if(words[index+1] == (myMap[words[index]])[j].first){
                present = 1;
                ++((myMap[words[index]])[j].second);
                break;
              }
            }
            if(present == 0){
              myMap[words[index]].push_back(make_pair(words[index+1], 1));
            }
          }
          else{
            myMap[words[index]] = {{words[index+1], 1}};
          }
        }
        myMap[words[words.size()-1]] = {};
      }
    }
    cout << "end constructor" << endl;
  }

  /**
 * Suppose you're in the middle of generating a document and that you've just added the word prevWord
 * to the document. generateNextWord(prevWord) should generate the next word at random for the document,
 * according to the frequencies of all the words that followed prevWord in the input documents
 *
 * So, for instance, if in all the input documents the word "foo" was followed by the word "bar" twice and "baz" 8 times,
 * then 80% of the time generateNextWord("foo") should return "baz" and 20% of the time you should return "bar".
 * 
 * This method should return punctuation words like "." and "," as if they were any other word.
 * Likewise, it should be able to take punctuation words as input (generateNextWord(","))
 * 
 * You can assume that prevWord is always a word that's present in one of the documents you've read in.
 */
  string generateNextWord(const string prevWord) {
    cout << "Begin generate next word for " << prevWord << endl;
    //cout << "myMap[prevWord[0] is " << myMap[prevWord][0].first << endl;

    vector<pair<string, int>> pairArr = myMap[prevWord];

    for(int index = 1; index < pairArr.size(); ++index){
     // cout << "Got vector of pairs. String is " << pairArr[index].first << " and int is " << pairArr[index].second;
      pairArr[index].second = pairArr[index].second + pairArr[index-1].second;
    }
    int sum = pairArr[pairArr.size()-1].second;
    srand(time(NULL));
    int randomNum = rand() % sum + 1; //range from 1 to sum

    string result;
    for(int index = pairArr.size()-1; index >= 0; --index){
      if(pairArr[index].second < randomNum){
        result = pairArr[index+1].first;
        break;
      }
    }

    return result; //TODO
  }

  /**
 * Generate a document with numWords words in it.
 *
 * See the docs on generateNextWord for a description of what it means to generate a word.
 * After generating all the words - concatenate them all into a single string representing the entire document, and return that string.
 *
 * Notes:
 * The first word you generate should be as if the previous word was '.'
 * Your document should not contain whitespace except for spaces.
 * Your should insert a single space in front of each word except:
 * * Don't insert spaces in front of punctuation marks
 * * Don't insert a space at the start of the document
 * Punctuation "words" count against this word total.
 *
 * The document will likely not end at the end of a sentence. That's okay.
 */
  string generateDocument(const int numWords) {
    cout << "begin generate document" << endl;
    cout << "my map size is " << myMap.size() << endl;

    string curr = generateNextWord(".");
    string result = curr;

    //cout << "1st result is " << result << endl;

    for(int index = 1; index < numWords; ++index){
      curr = generateNextWord(curr);
      bool addSpace = 1;
      for(int j = 0; j < PUNCTUATION.length(); ++j){
        if(curr[0] == PUNCTUATION[j]){
          addSpace = 0;
          break;
        }
      }
      if(addSpace == 1){
        result = result + " " + curr;
      }
      else{
        result = result + curr;
      }
    }

    return result;//TODO
  }

  ~DocumentGenerator() {
    //TODO
  }
  
  //Feel free to put your own code here

private:
  const string PUNCTUATION = ".!,?";
  const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";

  //Feel free to put your own code here
};

#endif //DOCUMENT_GENERATOR_HPP

