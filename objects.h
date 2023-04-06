#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Cell {
  int value;
  bool mergeable = false;

  Cell(int _value) : value(_value), mergeable(_value != 0 && _value != 2048) {}
  bool attemptToMerge(int otherCellValue) {
    if (mergeable && value == otherCellValue) {
      value *= 2;
      mergeable = false;
      return true;
    }
    return false;
  }
};

struct node{
  vector<vector<int>> m;
  string sequence;
  node * next;
};

