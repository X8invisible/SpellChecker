#pragma once

int wordCount();
int compare(const void* a, const void* b);
char** buildDictionary(int w, int flag);
int search(char buffer[60],char** array);
int binarySearch(char buffer[60], char** array);
