#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define MAX_ROW 1000    //input file will have less than or equal to 1000 lines
#define MAX_LEN 1000
#define MAX_TOKEN 100

    char* trim(char* token) {
        if (!token)     //error checking
            return NULL;
        int i = 0;
        while (*token == ' ')       //remove leading spaces
            token++;
        for (i = strlen(token) - 1; i >= 0 && token[i] == ' '; i--);//remove trailing spaces
        token[i + 1] = '\0';
        return token;
    }

    main() {
        int i = 0,dataIndex = 0;
        FILE* input = fopen("..\\mytable.csv", "r");
        char* data[MAX_ROW];        // will store the file content
        char* token;
        char line[MAX_LEN];         //temporary placeholder for a line input from the file
        for (; fscanf(input, "%[^\n]\n", line) != EOF; i++) {
            data[dataIndex] = (char*)malloc(strlen(line) + 1);//+1 for \0
            strcpy(data[dataIndex++], line);
        }
        fclose(input);
        FILE* output = fopen("..\\mytable.tl5", "w");
        for (i = 0; i < dataIndex; i++) {
            token = trim(strtok(data[i], ","));     //tokenizes the ith row stored in data[i] and trims it
            fprintf(output, "%-5.5s", token);
            while ((token = trim(strtok(NULL,","))))
                fprintf(output, "|%-5.5s", token);
            fprintf(output, i == dataIndex - 1 ? "" : "\n");
        }
        fclose(output);
    }

