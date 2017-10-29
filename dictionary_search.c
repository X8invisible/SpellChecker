#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary_search.h"

//sorts the array when the '-c' arg is used along with qsort
int compare(const void* a, const void* b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;

    return strcmp(*ia, *ib);
}

/*
  Gets the words from the dictionary file and puts them into an array
  method takes in the size of the dictionary
  and the flag for if "-c" argument is used
*/
char** buildDictionary(int size, int flag)
{
	FILE* dictionary;
	dictionary = fopen("dictionary.txt", "r");
	int i=0,j,length;
	char line[256];
  //allocates memory for the number of elements in the dictionary file
	char** array = malloc(size* sizeof(char*));
  //loop for reading and adding words to the array, one at a time
	for( int i=0;i<size;++i)
	{
    //reads one word
		fscanf(dictionary, "%s", line);
    //gets length
		length=strlen(line);
    //if the user specified the '-c' argument, it lowercases the word
		if(flag)
		for(j=0;j<length;j++)
				line[j]=tolower(line[j]);
    //allocates memory for the word
		array[i]=malloc(length* sizeof(char)+1);
    //copies the word to the current array index
		strcpy(array[i],line);

	}
  //if the -c arg is used the array must be sorted again using qsort
	if(flag)
		qsort(array, size, sizeof(char*), compare);

	fclose(dictionary);
//returns the completed array to the main program
	return array;
}

//this is just a method for counting the number of words in the dictionary file
int wordCount()
{
	int size=0;
	char line[60];
	FILE* dictionary;
	dictionary = fopen("dictionary.txt", "r");
  //the loop reads one word at a time and counts the words
	while ( !feof(dictionary))
	{
fscanf(dictionary, "%s", line);
		size++;
	}
	fclose(dictionary);
  //returns the number of words
	return size;
}

/*
the binary search algorithm for finding if a word is in the dictionary array
program takes in the word to be compared(buffer) and the dictionary array
*/
int binarySearch(char buffer[60], char** array)
{
	int exists = 0, ok=1, low=0, length, size=wordCount();
	int high = size;
	for(int i=0; i<size;i++)
	{
    //loop ends when the word is found or when the search area becomes empty
		while (low <= high && exists == 0)
		{
			int j=0;
      //gets the middle value between the ends of the search area
			int mid = (high+low)/2;
      /*
      checks if the word given is the same as the
      middle one(0 means they are the same word)
      */
			if(strcmp(array[mid],buffer) == 0)
			{
				exists = 1;
			}else
          /*if the given word is bigger(further in the alphabet) than the
           middle word then the search area is reduced to the upper half
          */
					if(strcmp(array[mid],buffer) < 0)
						low = mid+1;
          /*or or if the middle word is further than the given word
            the search area is reduced to the lower half
          */
					else
						high = mid-1;

					}
		}

//returns 1 or 0 if the word has been found or not
	return exists;
}
