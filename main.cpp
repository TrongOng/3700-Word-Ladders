#include <iostream>
#include <fstream>
#include "linearlist.h"
#include "linearlist-implementation.h"
#include "queue.h"

using namespace std;

Queue<int> myQueue;

void genLadder(int, int);
int hammingDistance(string, string);
int search(string);
void genAdjacency();

struct Word {
    string word;
    int ptr;
    LinearList<int> list;
};
Word wordList[5757];

int main() {

    

    fstream myFile;
    myFile.open("sgb-words.txt", ios::in); //read
    if (myFile.is_open()) {
        string line;
        int i = 0;
        while (getline(myFile, line)) {
            wordList[i].word = line;
            wordList[i].ptr = -1; //hamming


            i++;
        }
    }
    myFile.close();


    genAdjacency();

    Word inputWord1, inputWord2;
    cout << "Enter Words" << endl;
    cin >> inputWord1.word >> inputWord2.word;

    inputWord1.ptr=search(inputWord1.word);
    inputWord2.ptr=search(inputWord2.word);

    if(inputWord1.ptr == -1) {
        cout << "First word not in list" << endl;
        return 0;
    }
    if(inputWord2.ptr == -1) {
        cout << "Second word not in list" << endl;
        return 0;
    }
    genLadder(inputWord1.ptr, inputWord2.ptr);



    return 0;
}
void genAdjacency() {
        for (int i = 0; i < 5757; i++) {
            for (int j = 0; j < 5757; j++) {
                if(hammingDistance(wordList[i].word, wordList[j].word) == 1) { //compare first + second index of wordList by hamming
                    wordList[i].list.insert(wordList[i].list.size(), j); //insert into (empty index)
                }
            }
        }
}

void genLadder(int w1, int w2) {
    //v = index of someword
    //w = index of someword
    int w, v;
    //add w2 to a queue Q
    myQueue.enqueue(w2);
    
    //while Q is not empty do
    while (!myQueue.isEmpty()) {
        //dequeue Q into w
        w = myQueue.dequeue();
        
        //for each word v in w.list do
        for(int i = 0; i < wordList[w].list.size(); i++) {
            v = wordList[w].list[i];
        
            //if v.ptr = NULL and v != w2 then
            if(wordList[v].ptr == -1 && v != w2) {
                
                //v.ptr <- w
                wordList[v].ptr = w;
                //enqueue v in Q
                myQueue.enqueue(v);
            }
            //end if
        //end for
        }
    }
    //end while
    //if w1.ptr != NULL then
    if(wordList[w1].ptr != -1) {
        cout << wordList[w1].word << endl;
        //output w1
        //w <- w1.ptr
        w = wordList[w1].ptr;

        //while w != NULL do
        while(w != -1) {

            //output w
            cout << wordList[w].word << endl;
            //w = w.ptr

            w = wordList[w].ptr;
        }
        //end while
    }
    //else
    else {
        //no ladder exists
        cout << "No Ladder Exists" << endl;
    }
    //end if



}

//hamming distance
int hammingDistance(string w1, string w2)
{
    int count = 0;
    for (int i = 0; i < 5; i++){
        if (w1[i] != w2[i]){
            count++;
        }
    }
    return count;
}

int search(string w) { //ptr (index)
    //string arr[6] = w1;
    for (int i = 0; i < 5757; i++) {
        if (wordList[i].word == w) {
            return i;
        }
    }
    return -1;
}