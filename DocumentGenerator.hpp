/**
 * CSE 100 PA2 SpeechBuilder
 * Author: Jonathan Margoliash
 */

#ifndef DOCUMENT_GENERATOR_HPP
#define DOCUMENT_GENERATOR_HPP

#include <string>
#include <dirent.h>
#include <unordered_map>
#include "myUtils.hpp"
#include <algorithm>

using namespace std;

typedef unordered_map<string, vector<string>> pairMap;

/*
  static string * myKey;
  bool foundString(pair<string, int> & myPair){
    return (myPair.first == *myKey);
  }
*/

class DocumentGenerator
{
public:
  pairMap myMap;
  //unordered_map<string, int> sumMap;

 
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
    DIR * dir;
    struct dirent *ent;

    srand(time(NULL));

    if((dir = opendir(documentsDirectory.c_str())) != NULL){
      while((ent = readdir(dir)) != NULL){

        vector<string> words = myUtils::getWords(documentsDirectory + "/" + ent->d_name);

        if(words.size() == 0){
          continue;
        }

        for(int index = 0; index < words.size()-1; ++index){
          //if((myMap.count(words[index])) != 0){
            myMap[words[index]].push_back(words[index+1]);
          //}
          //else{
           // myMap[words[index]] = {words[index+1]};
          //}
        }
      }
      closedir(dir);
    }
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
  string generateNextWord(const string & prevWord) {
    string result;
 
    if(myMap[prevWord].size() == 1){
      result = myMap[prevWord][0];
      return result;
    }

    int sum = myMap[prevWord].size();

    int randomNum = rand() % sum; //range from 0 to sum-1

    result = myMap[prevWord][randomNum];

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
    string curr = generateNextWord(".");
    string result = curr;

    for(int index = 1; index < numWords; ++index){
      curr = generateNextWord(curr);

      if (PUNCTUATION.find(curr[curr.length()-1]) == string::npos) {
        result += " " + curr;
      } 
      else{
        result += curr;
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

