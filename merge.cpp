#include <iostream>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
#include <string>
#include <stack>
#include <cmath>
#include "Queue.h"
//#include <queue>
#include "objects.h"
//SEGMENTATION FAULT is at line 272
//specifically after the dequeue is called
using namespace std;

int sum(vector<vector<int>> matrix, size_t size) {
  int s = 0;
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
      if (matrix[i][j] != 2048)
        s += matrix[i][j];
  return s;
}

bool isPowerOfTwo(int n) {
  if (ceil(log2(n)) == floor(log2(n)))
    return true;
  return false;
}

bool isSolved(vector<vector<int>> matrix) {
  bool flag = false;
  for (int i = 0; i < matrix.size(); i++)
    for (int j = 0; j < matrix.at(i).size(); j++)
      if (matrix[i][j] != 0 && matrix[i][j] != 2048) {
        if (flag)
          return false;
        flag = true;
      }
  return true;
}

vector<vector<int>> moveU(vector<vector<int>> m){
  int size = m.size();
  
  for(int j = 0; j < size; j++){
    stack<Cell> s;
    int count = 0;
    
    for(int i = 0; i <= size; i++){
      if(i == size || m[i][j] == 2048){
        while (count > s.size()) {
          s.push(Cell(0));
        }
        for (int z = i - 1; z >= i - count; z--) {
          m[z][j] = s.top().value;
          s.pop();
        }
        count = -1;
      }
      else if(m[i][j] != 0) {
        if (s.empty() || !s.top().attemptToMerge(m[i][j])) {
          s.push(Cell(m[i][j]));
        }
      }
      count += 1;
    }
  }

  return m;
}

vector<vector<int>> moveR(vector<vector<int>> m){
  int size = m.size();
  
  for(int i = 0; i < size; i++){
    stack<Cell> s;
    int count = 0;
    
    for(int j = size - 1; j >= -1; j--){
      if(j == -1 || m[i][j] == 2048){
        while (count > s.size()) {
          s.push(Cell(0));
        }
        for (int z = j + 1; z <= j + count; z++) {
          m[i][z] = s.top().value;
          s.pop();
        }
        count = -1;
      }
      else if(m[i][j] != 0) {
        if (s.empty() || !s.top().attemptToMerge(m[i][j])) {
          s.push(Cell(m[i][j]));
        }
      }
      count += 1;
    }
  }

  return m;
}

vector<vector<int>> moveL(vector<vector<int>> m){
  int size = m.size();
  
  for(int i = 0; i < size; i++){
    stack<Cell> s;
    int count = 0;
    
    for(int j = 0; j <= size; j++){
      if(j == size || m[i][j] == 2048){
        while (count > s.size()) {
          s.push(Cell(0));
        }
        for (int z = j - 1; z >= j - count; z--) {
          m[i][z] = s.top().value;
          s.pop();
        }
        count = -1;
      }
      else if(m[i][j] != 0) {
        if (s.empty() || !s.top().attemptToMerge(m[i][j])) {
          s.push(Cell(m[i][j]));
        }
      }
      count += 1;
    }
  }

  return m;
}

vector<vector<int>> moveD(vector<vector<int>> m){
  int size = m.size();
  
  for(int j = 0; j < size; j++){
    stack<Cell> s;
    int count = 0;
    
    for(int i = size - 1; i >= -1; i--){
      if(i == -1 || m[i][j] == 2048){
        while (count > s.size()) {
          s.push(Cell(0));
        }
        for (int z = i + 1; z <= i + count; z++) {
          m[z][j] = s.top().value;
          s.pop();
        }
        count = -1;
      }
      else if(m[i][j] != 0) {
        if (s.empty() || !s.top().attemptToMerge(m[i][j])) {
          s.push(Cell(m[i][j]));
        }
      }
      count += 1;
    }
  }

  return m;
}

void addPath(Queue &q, Pair p, int d) {
    Pair temp;
    temp.matrix = p.matrix;
    temp.path = p.path;
    switch (d) {
        case 1:
            moveU(temp.matrix);
            if (temp.matrix != p.matrix) {
              temp.path += "1";
              q.push(temp);
            }
            break;
        case 2:
            moveR(temp.matrix);
            if (temp.matrix != p.matrix) {
              temp.path += "2";
              q.push(temp);
            }
            break;
        case 3:
            moveD(temp.matrix);
            if (temp.matrix != p.matrix) {
              temp.path += "3";
              q.push(temp);
            }
            break;
        case 4:
            moveL(temp.matrix);
            if (temp.matrix != p.matrix) {
              temp.path += "4";
              q.push(temp);
            }
            break;
    }
}
//bool isUnique(vector<vector<int>> m, int size)

bool isCompletelyMerged(const vector<vector<int>>& grid){
  int size = grid.size();
  //int n = 0;
  bool flag = false;
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if(grid[i][j] != 0 && grid[i][j] != 2048){
        if(flag)
          return false;
        flag = true;
      }
    }
  }
  
  return true;
}


/* function used to display matrix for debugging purposes */
void displayMatrix(vector<vector<int>> matrix) {
  for (vector<int> row : matrix) {
    for (int element : row) {
      cout << element << " ";
    }
    cout << endl;
  }
}


int main(int argc, char *argv[])
{
    ArgumentManager am (argc, argv);
    string input = am.get("input");
    string output = am.get("output");

    ifstream ifs(input);
    ofstream ofs(output);

    int size;
    int val;
    ifs >> size;
    vector<vector<int>> matrix;
    Queue q;
    Pair n;
    //stack<int>stk;
 

    for (int i = 0; i < size; i++)
    {
        vector<int> temp;
        for(int j = 0; j < size; j++){
            ifs >> val;
            temp.push_back(val);
        }
        matrix.push_back(temp);
    }
     n.matrix = matrix;
    n.path = "";
    q.push(n);
    //pushes in initial matrix
    cout << "Hello" << endl;
    while(!q.isEmpty()) {
    Pair p = q.pop();
    if (p.path.length() > 12) {
      ofs << "Impossible";
      break;
    }
    if (isSolved(p.matrix)) {
      if (p.path == "")
        ofs << "0";
      else {
        ofs << p.path;
      }
      break;
    }
    addPath(q, p, 1);
    addPath(q, p, 2);
    addPath(q, p, 3);
    addPath(q, p, 4);
  }
  
  return 0;
}
    //cur = nullptr;

/*

int sum(vector<vector<int>> matrix, size_t size) {
  int s = 0;
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
      if (matrix[i][j] != 2048)
        s += matrix[i][j];
  return s;
}

bool isPowerOfTwo(int n) {
  if (ceil(log2(n)) == floor(log2(n)))
    return true;
  return false;
}

bool isSolved(vector<vector<int>> matrix) {
  bool flag = false;
  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
      if (matrix[i][j] != 0 && matrix[i][j] != 2048) {
        if (flag)
          return false;
        flag = true;
      }
  return true;
}


*/