/*
File: Assignment2.cpp
Created by: Julia Troni
Creation Date: 1/26/2020
Synopsis: Program to analyzze the word frequency in a document 
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

struct wordItem {
  string word;
  int count;
};


void getStopWords (const char *ignoreWordFileName, string ignoreWords[]);
bool isStopWord (string word, string ignoreWords[]);
int getTotalNumberNonStopWords (wordItem uniqueWords[], int length);
void arraySort (wordItem uniqueWords[], int length);
void printNext10 (wordItem uniqueWords[], int N, int totalNumWords);

int main(int argc, char const *argv[])
{
    //checking command line arguments
    if (argc != 4)
    {
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" <<endl;

        return 0;
    }

    string ignoreWords[50];
    getStopWords(argv[3], ignoreWords);

    int numTimesDoubled=0;
    int maxSize=100; 
    int wordsSoFar;
    wordItem *uniqueWords= new wordItem[maxSize];

    //stream to open file
    ifstream TomFile(argv[2]);
    //checking if file opens
    if (!TomFile.is_open())
    {
        cout << "Failed to open " << argv[2] << endl;
    }

    //reading in words and checking storing unique words into the array of structs
    while (TomFile.good())
    {
        string stuff; 
        TomFile >> stuff;
        if (isStopWord(stuff,ignoreWords) == false)
        {
            int flagunique=1;
            for (int i=0; i< maxSize; i++)
            {
                if (stuff==uniqueWords[i].word)
                {
                    uniqueWords[i].count+=1;
                    flagunique=0; 
                }
            }
            if (flagunique==1)
            {
                if (maxSize==wordsSoFar)
                {
                    //array doubling
                    maxSize= 2*maxSize;
                    wordItem *temp = new wordItem[maxSize];
                    numTimesDoubled=numTimesDoubled+1;
                    
                    //copy the contents of array pointed to by a into temp array 
                    // n elements of array pointed to by temp
                    for (int i=0; i < maxSize/2; i++)
                    { 
                        temp[i]=uniqueWords[i];
                    }
                   // uniqueWords=temp;
                    delete [] uniqueWords;
                    uniqueWords = temp;

  
                }
                uniqueWords[wordsSoFar].word= stuff;
                uniqueWords[wordsSoFar].count = 1;
                wordsSoFar=wordsSoFar+1;
            }
        }
        
    }


    int totalNonCommon = getTotalNumberNonStopWords(uniqueWords,wordsSoFar);
    arraySort(uniqueWords, wordsSoFar);

    cout << "Array doubled: " << numTimesDoubled << endl << "#" << endl;
    cout << "Unique non-common words: " << wordsSoFar-1 << endl << "#" << endl;
    cout << "Total non-common words: " << totalNonCommon << endl << "#" << endl;
    cout << "Proablitiy of next 10 words from rank " << argv[1] << endl;
    cout << "---------------------------------------" <<endl;
    printNext10(uniqueWords, stoi(argv[1]), totalNonCommon);

    TomFile.close(); //closing the file
    
    delete [] uniqueWords; //return memory to heap

    

    return 0;
}


//function getStopWords() reads the stop words from the ignore word file and stores them in an array
void getStopWords (const char *ignoreWordFileName, string ignoreWords[])
{
    //stream to open file
    ifstream ignoreFile(ignoreWordFileName);
    //checking if file opens
    if (!ignoreFile.is_open())
    {
        cout << "Failed to open " << ignoreWordFileName << endl;
    }

    //reading in ignore words and storing them into the array
    while (ignoreFile.good())
    {
        for (int i=0; i < 50; i++)
        {
            string stuff; 
            getline(ignoreFile, stuff);
            ignoreWords[i]= stuff;
        }
    }

    ignoreFile.close(); //closing the file
}

//function isStopWord() returns wheter the word is in the ignoreWords array
bool isStopWord (string word, string ignoreWords[])
{
    bool isStop= false; 
    for (int i=0; i < 50; i++)
    {
        if (word == ignoreWords[i])
        { 
            isStop = true;
        }
    }

    return (isStop);
}

//function getTotalNumberNonStopWords() computes the total number of words in the entire document by summing up all the couts of the individaul unique words
int getTotalNumberNonStopWords (wordItem uniqueWords[], int length)
{
    int totalWords=0; 
    for (int i=0; i<length; i++)
    {
        totalWords= totalWords + uniqueWords[i].count;
    }

    return (totalWords);
}

//function arraySort() sorts the uniqueWords array by word count, putting the most frequent words first
void arraySort (wordItem uniqueWords[], int length)
{
    for (int i=0; i< length; i++)
    {
        for (int j=i+1; j < length; j++)
        {
            if (uniqueWords[i].count < uniqueWords[j].count)
            {
                wordItem temp;
                temp= uniqueWords[i];
                uniqueWords[i]= uniqueWords[j];
                uniqueWords[j]=temp;
            }
        }
    }
}

//function printNext10() prints the next 10 words after the starting index N from the sorted array of unique words. They are printed with their probability occurence up to 4 decimal places 
void printNext10 (wordItem uniqueWords[], int N, int totalNumWords)
{
   for (int i=N; i< (N+10); i++)
    {
        double probOfOccur= uniqueWords[i].count/double(totalNumWords);

        cout << fixed << setprecision(4) << probOfOccur << " - " << uniqueWords[i].word << endl;
    }
}