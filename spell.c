#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary_search.h"
/*
author: Ovidiu-Andrei Radulescu 40283288
date last modified: Friday February 24th 2017
This is a spell checking program
*/


int main(int argc, char **argv)
{
int i,j,firstWord = 1,size= wordCount(),count=1, check = 0,line=1,length;
int iFlag=0, oFlag=0, cFlag=0, singleLineChecker=1, singleWords=0;
char backup[60]="",c, buffer[60];
fpos_t position;
FILE *input;
FILE *output;
//just a simple graphical addition to make it look nicer
printf(" ********************** \n");
printf(" *                    * \n");
printf(" *   Spell Checking   * \n");
printf(" *      Software      * \n");
printf(" *                    * \n");
printf(" *  Andrei Radulescu  * \n");
printf(" *                    * \n");
printf(" ********************** \n\n");
//checks for arguments and switches the respective flags to 1 if argument found
if (argc == 1)
{
	printf(" Default settings in use\n");

}
else
	for (i = 1; i < argc; i++ )
{
  if (!strcmp(argv[i], "-i"))
  {
	input = fopen(argv[++i], "r");
	if(input ==NULL)
	{
		printf("ERROR: Wrong file name\n");
		exit(0);
	}
	iFlag = 1;

  }
	if(!strcmp(argv[i], "-o"))
	{
		output= fopen(argv[++i], "w");
		fprintf(output," ********************** \n");
		fprintf(output," *                    * \n");
		fprintf(output," *   Spell Checking   * \n");
		fprintf(output," *      Software      * \n");
		fprintf(output," *                    * \n");
		fprintf(output," *  Andrei Radulescu  * \n");
		fprintf(output," *                    * \n");
		fprintf(output," ********************** \n\n");
		oFlag =1;
	}
	if(!strcmp(argv[i], "-c"))
	{
		cFlag =1;
	}
}
//notifies the user of what's in use
	if(iFlag == 0)
  {

	  printf(" Console shall be used for input\n");
  }
  if(oFlag == 0)
	{
		printf(" Console shall be used for output\n");
	}
//gets the array of dictionary words
char** array= buildDictionary(size, cFlag);

//the algorithm for spell checking a file
if(iFlag == 1)
{
	//does the loop until there are no more words in the file
	while ( !feof(input))
	{

		fscanf(input,"%s", buffer);
		//checks if the file has one word per line or not(only does it once)
		if(singleLineChecker==1)
		{
			singleLineChecker =0;
			//checks the next two characters after the first word of the file
			if(fgetc(input)=='\n'||fgetc(input)=='\n')
			{
				singleWords=1;
				//the else goes back in case letters have been read
			}else fseek(input,-2, SEEK_CUR);
		}
		//printf("things\n");
		//gets the length of the word
		length = strlen(buffer);
		//if the user requests '-c' argument the whole word will be lowercased
		for(i = 0;i<length;i++)
		{
			if(cFlag)
				buffer[i] = tolower(buffer[i]);
		}
		//removes commas from the end of a word
			if(buffer[length-1] == ',')
				buffer[length-1]='\0';
		/*
		checks if the word is supposed to be the first word of a sentence and
		lowercases the first letter, but copies the string to a backup in case the
		word is supposed to be written with an uppercase(for example names)
		*/
				strcpy(backup,buffer);
				if(firstWord == 1)
				{
					strcpy(backup,buffer);
					buffer[0] = tolower(buffer[0]);
					firstWord = 0;
				}
			/*
				the loop removes end of sentence punctuation marks from the end of the word and
			 	notifies the program that the next word will be the start of a new sentence
			 */
			count = 1;
			if(buffer[length-1] == '.' || buffer[length-1] == '?' || buffer[length-1] == '!')
			//this removes multiple punctuation marks
			{	do
				{
				buffer[length-count++]='\0';
				firstWord=1;
			}while(buffer[length-count]=='.' || buffer[length-count]=='?' || buffer[length-count]=='!');
			}
	//verifies if a word is in the dictionary array and prints it to console(or file) if it doesn't
		if(!(binarySearch(buffer, array)) && !(binarySearch(backup, array)))
		//checks which option was selected for output(file or console)
			if(oFlag == 0)
				printf(" word: %s		line: %d\n", buffer, line);
			else
				fprintf(output, " word: %s 	line: %d\n", buffer, line);

				/*counts words if the file is the signle words type
					otherwise searches for a newline character
					*/
				if(singleWords)
					line++;
				else
				{
				   //this gets the next character after a word
					//checks if it indicates a new line and increases counter
							if(fgetc(input)=='\n')
							{
								line++;
					//checks again in case there's an empty line
								if(fgetc(input)=='\n')
									line++;
							}
				}
			}

	fclose(input);
}
else
	{
//the algorithm for spell checking a sentence(or word) inputted on the console
	printf(" Enter your sentence(CTRL+C ends the program): ");
	while(scanf("%s", buffer)!=EOF)
		{
		//same algorithm as the file part
		count = 1;
		length = strlen(buffer);
		if(cFlag)
			for(i = 0;i<length;i++)
				buffer[i] = tolower(buffer[i]);
				//same algorithm as the file one

			if(buffer[length-1] == ',')
				buffer[length-1]='\0';

				if(firstWord == 1)
				{
					buffer[0] = tolower(buffer[0]);
					firstWord = 0;
				}

			 if(buffer[length-1] == '.' || buffer[length-1] == '?' || buffer[length-1] == '!')
			{	do
				{
				buffer[length-count++]='\0';
				firstWord=1;
				}while(buffer[length-count]=='.' || buffer[length-count]=='?' || buffer[length-count]=='!');
			}
		if(!(binarySearch(buffer, array)) && !(binarySearch(backup, array)))
			if(oFlag == 0)
				printf(" word: %s		line: %d\n", buffer, line);
			else
				fprintf(output, " word: %s		line: %d\n", buffer, line);
				//counts new lines
				c = fgetc(stdin);
				if(c=='\n')
					line++;

		}
	}

//closes the output file if the user specified one
if(oFlag)
{
	fclose(output);
	printf(" Program has finished, check your output file\n");
}

	return 0;
}
