// CPSC 5600 - String Similarity
//
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <unordered_map>
using namespace std;

#include "tbb/tbb.h"
using namespace tbb;

unordered_map<int, char&> vowelsMap;
unordered_map<int, char&> consoMap;
string vows = "aeiou";
string cons = "bcdfghjklmnpqrstvwxyz";
int min(int a, int b, int c){
    int x =(a < b)? a : b;
    x = (x < c)? x : c;
return x;
}

class Matrix {

public:
    Matrix(int _rows, int _cols) {
        rows = _rows;
        cols = _cols;
        Arr = new int[rows * cols];
    }

    int &operator()(int i, int j) {
        return Arr[i * cols + j];
    }
    
private:
    int* Arr;
    int rows;
    int cols;
void printMatrix(ofstream &out) {
        for (int l = 0; l < rows; l++) {
            for (int m = 0; m < cols; m++) { out << (*this)(l, m) << " "; }
            out << endl;
    }
    
    }
};

int optimal( string A, string B, int sizeA, int sizeB){
    Matrix arr(sizeA+1,sizeB+1);
    for (int i = 0; i < sizeA +1; i++){
        arr(i,0) = i*2;
    }
    for(int j = 0; j < sizeB+1; j++){
        arr(0,j) = j*2;
    }
//initialize to zeroes
    for (int o =1; o < sizeA+1; o++){
         for (int p = 1; p < sizeB+1; p++){
            arr(o,p) = 0;
         }
     }

   for (int k = 0; k < sizeA; k++){
       for (int l = 0; l < sizeB; l++){
            int score = 0;
             if(A[k] == B[l]){
                score = 0;}
            else { //calculate mismatch type
                //if letter in first is a consonant
                if ((cons.find(A[k]) != string::npos) && (cons.find(B[l]) != string::npos)){
                    score = 1;
                }
                else if ((vows.find(A[k]) != string::npos) && (vows.find(B[l]) != string::npos)){
                    score = 1;
                }
                else{ score = 3; }
            }
             int align = arr(k,l) + score;
             int gapB = arr(k,l+1) + 2;
             int gapA = arr(k+1,l) + 2;
             arr(k+1,l+1) = min(align, gapA, gapB);
            // matrix filled
	}
    }
      cout << endl;
    //  cout << " Possible score: " << arr(sizeA-1, sizeB-1) << endl;
      return arr(sizeA, sizeB);
}
int main(int argc, char *argv[])
{
  int answer;
  // Check for invalid command lines
  if (argc != 2) {
    cerr << "Invalid command line - usage: <input file>" << endl;
    exit(-1);
  }

  // Start the timer
  tick_count start_time = tick_count::now();

    ifstream ifile(argv[1]);

    // Read in the file
    string first;
    ifile >> first;
    string second;
    ifile >> second;
    ifile.close();

  // TODO: Perform the algorithm
  answer = optimal(first, second, first.length(), second.length());
  // Stop the timer
  tick_count end_time = tick_count::now();
  double run_time = (end_time - start_time).seconds();

  // Print the results
  cout << "Answer: " << answer << endl;
  cout << "Time:   " << run_time << endl;

  return 0;
}
