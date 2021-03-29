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
    void toCSV(char* inFile,char* outFile, char* inType){
        printf("\ninput file-> %s, output file-> %s, changing .csv to .%s\n", inFile, outFile, inType);
    }
    void toTC9(char* inFile,char* outFile, char* inType){
        printf("\ninput file-> %s, output file-> %s, changing .tc9 to .%s\n", inFile, outFile, inType);
    }
    void toTL5(char* inFile,char* outFile, char* inType){
        printf("\ninput file-> %s, output file-> %s, changing .tl5 to .%s\n", inFile, outFile, inType);
    }
    void toTR9(char* inFile,char* outFile, char* inType){
        printf("\ninput file-> %s, output file-> %s, changing .tr9 to .%s\n", inFile, outFile, inType);
    }
    char getCommandWord(char command[], int maxLength) {
        char lastCharacter;//either space or new line
        int i;
        for (i = 0; (lastCharacter = getchar()) == ' '; i++);//skip leading white spaces
        if (lastCharacter == '\n') {
            command[0] = '\0';
            return lastCharacter;
        }
        command[0] = lastCharacter;
        for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
        lastCharacter = command[i];
        command[i] = '\0';
        return lastCharacter;
    }


    main() {
//      get user input
        char command[MAX_TOKEN];
        char inputFile[MAX_TOKEN];
        char outputFile[MAX_TOKEN];

        char inputTemp[MAX_TOKEN];
        char outputTemp[MAX_TOKEN];

        char *inputFileType;
        char *outputFileType;

        char lastCharacter1; //last character after receiving command word
        char lastCharacter2; //last character after input file
        char lastCharacter3; //last character after output file

        printf("Welcome to my file converter \navailable commands are: \n1- quit \n2- convert source.xxx destination.yyy \nsupported file types are .csv .tc9  .tl5 .tr9\n");
        while (1){ //infinite while loop...
            printf("Please enter a new command... quit or convert source.xxx destination.yyy\n ex: convert t.csv t.tl5 \n");
            lastCharacter1 = getCommandWord(command, MAX_TOKEN); //get first word from user input
            lastCharacter2 = getCommandWord(inputFile, MAX_TOKEN); //store input file
            lastCharacter3 = getCommandWord(outputFile, MAX_TOKEN); //store output file

            if (strcmp(command, "quit") == 0){ //if command === "quit"
                printf("Closing program...");
                break;
            }else if (!strcmp(command, "convert") && (lastCharacter1 != '\n') && (lastCharacter2 != '\n') && (lastCharacter3 == '\n')){ //checking that input is complete
//              use temp variables to keep inputFile and outputFile from changing
                strcpy(inputTemp, inputFile);
                strcpy(outputTemp, outputFile);

//              get the input/output file type
                strtok(inputTemp, ".");
                inputFileType = strtok(NULL, ".");
                strtok(outputTemp, ".");
                outputFileType = strtok(NULL, ".");

//              confirm all values
                printf("input file: %s \n", inputFile);
                printf("output file: %s \n", outputFile);
                printf("converting from %s to %s \n",inputFileType,outputFileType );

//                 check that file types are supported
                if( ((!strcmp(inputFileType, "csv")) || (!strcmp(inputFileType, "tc9")) || (!strcmp(command, "tl5")) || (!strcmp(command, "tr9")))
                && ((!strcmp(outputFileType, "csv")) || (!strcmp(outputFileType, "tc9")) || (!strcmp(outputFileType, "tl5")) || (!strcmp(outputFileType, "tr9"))) ){
                    printf(" file types accepted, processing request...\n");

                    if(!strcmp(outputFileType, "csv")){
                        toCSV(inputFile,outputFile, inputFileType);
                    }else if(!strcmp(outputFileType, "tc9")){
                        toTC9(inputFile,outputFile, inputFileType);
                    }else if(!strcmp(outputFileType, "tl5")){
                        toTL5(inputFile,outputFile, inputFileType);
                    }else if(!strcmp(outputFileType, "tr9")){
                        toTR9(inputFile,outputFile, inputFileType);
                    }
                }else{
                    printf("\nINVALID FILE TYPE! supported files are .csv .tc9 .tl5 .tr9\n");
                }
            }
            else {
                printf("\n invalid command! Your command must start either with quit or convert source.xxx destination.yyy\n");
                while (lastCharacter1 != '\n')//skip the remainder of my invalid command...
                    lastCharacter1 = getCommandWord(command, MAX_TOKEN);
            }
        }

//        int i = 0,dataIndex = 0;
//        FILE* input = fopen("..\\mytable.csv", "r");
//        char* data[MAX_ROW];        // will store the file content
//        char* token;
//        char line[MAX_LEN];         //temporary placeholder for a line input from the file
//        for (; fscanf(input, "%[^\n]\n", line) != EOF; i++) {
//            data[dataIndex] = (char*)malloc(strlen(line) + 1);//+1 for \0
//            strcpy(data[dataIndex++], line);
//        }
//        fclose(input);
//        FILE* output = fopen("..\\mytable.tl5", "w");
//        for (i = 0; i < dataIndex; i++) {
//            token = trim(strtok(data[i], ","));     //tokenizes the ith row stored in data[i] and trims it
//            fprintf(output, "%-5.5s", token);
//            while ((token = trim(strtok(NULL,","))))
//                fprintf(output, "|%-5.5s", token);
//            fprintf(output, i == dataIndex - 1 ? "" : "\n");
//        }
//        fclose(output);

    }

