#include "Controller.h"

#define printf_s printf

int Randomize(int minimumVal, int maximumVal) {

    int value = rand() % (maximumVal - minimumVal + 1) + minimumVal;
    return value;

}

void writeToFile(char filename[], char fileMode[2], char data[3]) {
    FILE *stream;
    stream = fopen(filename, fileMode);//a
    char newData[4];
    strcpy(newData, data);
    strcat(newData, "\n");
    fwrite(newData, sizeof(char), strlen(newData), stream);
    fclose(stream);
}

void newline(int linenumber) {

    for (int i = 0; i < linenumber; i++) {

        printf_s("\n");
    }
}

int FileCount(char filename[], int Count) {
    FILE *stream;
    int fileCoun = 0;
    char buffer[5];

    stream = fopen(filename, "r");//r
    if (stream != NULL) {


        while (fread(buffer, sizeof(char), 3, stream) > 0) {
            fileCoun++;
        }
    }


    fclose(stream);
    return fileCoun;
}

void ClearFile(char FileName[]) {
    FILE *stream;
    stream = fopen(FileName, "w");
    fclose(stream);

}

int maximumValue(int values[], int length) {
    int maximumV = 0;

    for (int j = 0; j < length; j++) {
        if (values[j] > maximumV) {
            maximumV = values[j];
        }
    }
    return maximumV;
}


void readFromFile(char filename[], char fileMode[2], char fields[][4], char Message[10]) {
    FILE *stream;

    char buffer[4];

    int readCount = 0;
    stream = fopen(filename, fileMode);
    if (stream != NULL) {


        while (fread(buffer, sizeof(char), 3, stream) > 0 && readCount < 52) {
            strcpy(fields[readCount], buffer);

            readCount++;

        }
        strcpy(Message, "OK");
    }
    {
        if (readCount != 52) {
            strcpy(Message, "Failed");
        }

    }

    fclose(stream);

}

char *readFromFile1(char filename[], char fileMode[2], int Count) {
    FILE *stream;
    char buffer[2];


    stream = fopen(filename, fileMode);
    fread(buffer, sizeof(char), Count, stream);
    char *finalSTring = buffer;
    return finalSTring;
}

void split(char splits[][50], char value[], char *splitChar) {
    int splitsCount = 0;

    char *buffer;

    buffer = strtok(value, splitChar);

    while (buffer != NULL) {
        strcpy(splits[splitsCount], buffer);
        buffer = strtok(NULL, splitChar);

        splitsCount++;
    }

}

void splitV3(char splits[], char value[], char splitChar) {
    int inter = 0;


    while (value[inter] == splitChar && value[inter]) {
        inter++;
        strcpy(splits, value + inter);
    }

}

void splitV2(char splits[][50], char value[], char *splitChar) {
    int splitsCount = 0;

    char *b1;
    char *b2;

    strcpy(splits[splitsCount], value);
    b2 = strtok_r(value, splitChar, &b1);

    while (b2 != NULL) {
        strcpy(splits[splitsCount], b2);
        b2 = strtok_r(NULL, splitChar, &b1);

        splitsCount++;
    }

}

int CharToInt(char c) {
    int h = c - '0';

    return h;
}

bool canSplit(char data[], char splitChar) {


    bool cansPlitMe = false;
    char *pos = strchr(data, splitChar);
    if (pos != NULL) {
        cansPlitMe = true;
    }
    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == splitChar) {
            cansPlitMe = true;
        }
    }
    return cansPlitMe;
}

void AfterSpaceChar(char data[], char buffer[]) {

    int len = strlen(data);

    int indexMe = 0;
    for (int i = 0; i < len; i++) {
        if (data[i] == ' ')
            indexMe = i;
    }

    memcpy(buffer, &data[indexMe + 1], len - (indexMe + 1));
    buffer[len - (indexMe + 1)] = '\0';
}
