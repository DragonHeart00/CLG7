#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>

int Randomize(int minimumVal,int maximumVal);

void writeToFile(char filename[],char fileMode[2], char data[3]);

int FileCount(char filename[],int Count);
void splitV2(char splits[][50], char value[],char* splitChar);
void readFromFile(char filename[],char fileMode[2],char fields [][4],char Message[10]);
char * readFromFile1(char filename[],char fileMode[2],int Count);
int maximumValue(int values[],int length);
  // Reading value from file
void splitV3(char splits[], char value[],char splitChar);
void split(char splits[][50], char value[],char* splitChar);
void newline(int linenumber);
void ClearFile(char FileName[]);
void AfterSpaceChar(char data[],char buffer[]);
bool canSplit(char data[],char splitChar);
int CharToInt(char c);

#endif // CONTROLLER_H_INCLUDED
