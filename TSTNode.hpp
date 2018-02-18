#ifndef TSTNODE_HPP
#define TSTNODE_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class TSTNode {

public:
  char const data;

  unsigned endWord;

  int frequency;

  TSTNode * left;
  TSTNode * mid;
  TSTNode * right;

  string myWord;

  /** Constructor.  Initialize a TSTNode with the given Data item,
   *  no children.
   */
  TSTNode(const char & d) : data(d) {
    left = right = mid = 0;
    endWord = 0;
    frequency = 0;
  }


};
#endif
