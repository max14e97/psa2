/**
 * CSE 100 PA2 SpeechBuilder
 * Author: Jonathan Margoliash
 */

#ifndef DOCUMENT_GENERATOR_HPP
#define DOCUMENT_GENERATOR_HPP

#include <string>

using namespace std;

class DocumentGenerator
{
public:

  
 /**
 * Builds a document generator from the documents in the given directory
 * This should open all files in the directory, reads them in, tokenize them into words,
 * and build the datastructure from that stream of words.
 *
 * To tokenize a document:
 * * remove all UNWANTED_CHARACTERS from the document
 * * split it into different tokens based on whitespace (treat all whitespace breaks equally)
 * * additionally split each PUNCTUATION character into its own token (so a single period is a 'word')
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
 * 2) pretend that the first word in the document is preceeded by a periood (That way, it is considered when starting any new sentence)
 */
  DocumentGenerator(const string documentsDirectory) {
    //TODO
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
    return ""; //TODO
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
 * 
 * The document will likely not end at the end of a sentence. That's okay.
 */
  string generateDocument(const int numWords) {
    return "";//TODO
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

