#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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
//    ex: convert t.tl5 t.csv
    void toCSV(char* inFile,char* outFile, char* inType){
    /*
    *   .csv (comma separated values) file: stores tabular data in plain text. Each line of the file represents a table row containing one or more cells separated by commas.
    */
        printf("\ninput file-> %s, output file-> %s, changing .%s to .csv\n", inFile, outFile, inType);

        char* delimiter; //allows to split file either by commas or |
        if((!strcmp(inType, "csv"))){ delimiter = ",";  }else{  delimiter = "|"; }
        printf("delimiter: %s \n", delimiter);

        char inTemp[MAX_TOKEN]; //to keep original string unchanged
        char outTemp[MAX_TOKEN];
        char temp1[MAX_TOKEN] = "../"; //needed to find the file
        char temp2[MAX_TOKEN] = "../";

        strcpy(inTemp, inFile);
        strcpy(outTemp, outFile);

        strcat(temp1,inTemp); //need to add "../" at beginning of file path to avoid a pop up error
        strcat(temp2,outTemp);

        int i = 0,dataIndex = 0;

        FILE* input = fopen(temp1, "r");
        char* data[MAX_ROW];        // will store the file content
        char* token;
        char line[MAX_LEN];         //temporary placeholder for a line input from the file
        for (; fscanf(input, "%[^\n]\n", line) != EOF; i++) {
            data[dataIndex] = (char*)malloc(strlen(line) + 1);//+1 for \0
            strcpy(data[dataIndex++], line);
        }
        fclose(input);

        FILE* output = fopen(temp2, "w");
        for (i = 0; i < dataIndex; i++) {
            token = trim(strtok(data[i], delimiter));     //tokenizes the ith row stored in data[i] and trims it
            fprintf(output, "%s", token);
            while ((token = trim(strtok(NULL,delimiter))))
                fprintf(output, ",%s", token);
            fprintf(output, i == dataIndex - 1 ? "" : "\n");
        }
        fclose(output);
        printf("\n****** %s is ready to be viewed! ******\n\n\n", outFile);
    }

//    ex: convert t.csv t.tc9
    void toTC9(char* inFile,char* outFile, char* inType){
    /*
     *.tc9 file: stores tabular data in plain text. Each line of the file represents a table row
        containing one or more cells separated by ???|??? character. Each cell is 9-characters long
        and contains a center-aligned string. If the string stored in a cell has n < 9 characters,
        the rest of it will be filled with spaces; i.e. there will be be (9???n)/2 extra space characters in
        the cell before the string and (9???n)/2 extra space characters in the field after it. However,
        if a string with more than 9 characters and odd length is supposed to be placed in a
        cell, only its middle 9 characters is stored in the cell. In the case that the length of
        original string is even and greater than 9, its middle 8 characters must be stored in the
        cell (plus an extra space character).
     */
        printf("\ninput file-> %s, output file-> %s, changing .%s to .tc9\n", inFile, outFile, inType);

        char* delimiter; //allows to split file either by commas or |
        if((!strcmp(inType, "csv"))){ delimiter = ",";  }else{  delimiter = "|"; }
        printf("delimiter: %s \n", delimiter);

        int char_count;             //store how many extra chars are in original cell
        char inTemp[MAX_TOKEN];     //to keep original string unchanged
        char outTemp[MAX_TOKEN];
        char temp1[MAX_TOKEN] = "../";
        char temp2[MAX_TOKEN] = "../";
        char* data[MAX_ROW];        // will store the file content
        char* token;
        char line[MAX_LEN];         //temporary placeholder for a line input from the file
        int i = 0,dataIndex = 0, side_spaces = 0;
        strcpy(inTemp, inFile);
        strcpy(outTemp, outFile);
        strcat(temp1,inTemp);       //need to add "../" at beginning of file path to avoid a pop up error
        strcat(temp2,outTemp);

//    Storing input data
        FILE* input = fopen(temp1, "r");
        for (; fscanf(input, "%[^\n]\n", line) != EOF; i++) {
            data[dataIndex] = (char*)malloc(strlen(line) + 1);//+1 for \0
            strcpy(data[dataIndex++], line);
        }
        fclose(input);

//    Processing output data
        FILE* output = fopen(temp2, "w");

        for (i = 0; i < dataIndex; i++) {
            printf("Data[i] -> %s\n",data[i]);
            token = trim(strtok(data[i], delimiter));   //tokenizes the ith row stored in data[i] and trims it
            char_count = strlen(token); //store how many extra chars are in original cell

            printf("token -> %s .... char_count -> %d\n",token, char_count);

            if(char_count <= 9){
                side_spaces = round((float)(9 - char_count)/2);
                printf("side spaces %d\n",side_spaces);
                int y, z; //iterators
                for (y = 0; y < side_spaces; y++)
                    fprintf(output, " ");
                fprintf(output, "%s", token);
                for (z = 0; z < 9-char_count-side_spaces; z++)
                    fprintf(output, " ");
                fprintf(output, "|");

            }else{
                printf("token bigger than 9, only middle 9 chars will be saved\n");
                side_spaces = round((float)(char_count - 9)/2); //number that will start printing
                fprintf(output, "%.9s|", token+side_spaces);
            }

            while ((token = trim(strtok(NULL,delimiter)))) {
                char_count = strlen(token);
                printf("token -> %s .... char_count -> %d\n",token, char_count);

                if(char_count <= 9){
                    side_spaces = round((float)(9 - char_count)/2); // spaces on left side
                    printf("side spaces %d\n",side_spaces);
                    int y, z; //iterators
                    for (y = 0; y < side_spaces; y++)
                        fprintf(output, " ");
                    fprintf(output, "%s", token);
                    for (z = 0; z < 9-char_count-side_spaces; z++)
                        fprintf(output, " ");
                    fprintf(output, "|");

                }else{
                    printf("token bigger than 9, only middle 9 chars will be saved\n");
                    side_spaces = round((float)(char_count - 9)/2); //number that will start printing
                    fprintf(output, "%.9s|", token+side_spaces);
                }
            }

            fprintf(output, i == dataIndex - 1 ? "" : "\n");
        }
        fclose(output);
        printf("\n****** %s is ready to be viewed! ******\n\n\n", outFile);

    }

//    ex: convert t.csv t.tl5
    void toTL5(char* inFile,char* outFile, char* inType){
    /*
    * .tl5 file:  stores tabular data in plain text. Each line of the file represents a table row
    containing one or more cells separated by ???|??? character. Each cell is 5-characters long
    and contains a left-aligned string. If the string stored in a cell has n < 5 characters,
    the rest of it will be filled with spaces; i.e. there will be 5 ???n extra space characters in
    the field after the string. However, if a string with more than 5 characters is supposed
    to be placed in a cell, only its first 5 characters is stored in the cell.
    .
    */
        printf("\ninput file-> %s, output file-> %s, changing .%s to.tl5\n", inFile, outFile, inType);

        char* delimiter; //allows to split file either by commas or |
        if((!strcmp(inType, "csv"))){ delimiter = ",";  }else{  delimiter = "|"; }
        printf("delimiter: %s \n", delimiter);

        char inTemp[MAX_TOKEN]; //to keep original string unchanged
        char outTemp[MAX_TOKEN];
        char temp1[MAX_TOKEN] = "../";
        char temp2[MAX_TOKEN] = "../";

        strcpy(inTemp, inFile);
        strcpy(outTemp, outFile);

        strcat(temp1,inTemp); //need to add "../" at beginning of file path to avoid a pop up error
        strcat(temp2,outTemp);

        int i = 0,dataIndex = 0;

        FILE* input = fopen(temp1, "r");
        char* data[MAX_ROW];        // will store the file content
        char* token;
        char line[MAX_LEN];         //temporary placeholder for a line input from the file
        for (; fscanf(input, "%[^\n]\n", line) != EOF; i++) {
            data[dataIndex] = (char*)malloc(strlen(line) + 1);//+1 for \0
            strcpy(data[dataIndex++], line);
        }
        fclose(input);

        FILE* output = fopen(temp2, "w");
        for (i = 0; i < dataIndex; i++) {
            token = trim(strtok(data[i], delimiter));     //tokenizes the ith row stored in data[i] and trims it
            fprintf(output, "%-5.5s", token);
            while ((token = trim(strtok(NULL,delimiter))))
                fprintf(output, "|%-5.5s", token);
            fprintf(output, i == dataIndex - 1 ? "" : "\n");
        }
        fclose(output);
        printf("\n****** %s is ready to be viewed! ******\n\n\n", outFile);
    }
//    ex: convert t.csv t.tr9
    void toTR9(char* inFile,char* outFile, char* inType){
    /*
        .tr9 file: stores tabular data in plain text. Each line of the file represents a table row
        containing one or more cells separated by ???|??? character. Each cell is 9-characters long
        and contains a right-aligned string. If the string stored in a cell has n < 9 characters,
        the rest of it will be filled with spaces; i.e. there will be 9 ???n extra space characters in
        the cell before the string. However, if a string with more than 9 characters is supposed
        to be placed in a cell, only its last 9 characters is stored in the cell.

    */
        printf("\ninput file-> %s, output file-> %s, changing .%s to .tr9\n", inFile, outFile, inType);

        char* delimiter; //allows to split file either by commas or |
        if((!strcmp(inType, "csv"))){ delimiter = ",";  }else{  delimiter = "|"; }
        printf("delimiter: %s \n", delimiter);

        int char_count; //store how many extra chars are in original cell
        char inTemp[MAX_TOKEN]; //to keep original string unchanged
        char outTemp[MAX_TOKEN];
        char temp1[MAX_TOKEN] = "../";
        char temp2[MAX_TOKEN] = "../";

        strcpy(inTemp, inFile);
        strcpy(outTemp, outFile);

        strcat(temp1,inTemp); //need to add "../" at beginning of file path to avoid a pop up error
        strcat(temp2,outTemp);

        int i = 0,dataIndex = 0;

        FILE* input = fopen(temp1, "r");
        char* data[MAX_ROW];        // will store the file content
        char* token;
        char line[MAX_LEN];         //temporary placeholder for a line input from the file
        for (; fscanf(input, "%[^\n]\n", line) != EOF; i++) {
            data[dataIndex] = (char*)malloc(strlen(line) + 1);//+1 for \0
            strcpy(data[dataIndex++], line);
        }
        fclose(input);

        FILE* output = fopen(temp2, "w");

        for (i = 0; i < dataIndex; i++) {
            printf("Data[i] -> %s\n",data[i]);
            token = trim(strtok(data[i], delimiter));   //tokenizes the ith row stored in data[i] and trims it

            char_count = strlen(token); //store how many extra chars are in original cell
            printf("token -> %s .... char_count -> %d\n",token, char_count);

            if(char_count > 9){
                printf("token bigger than 9, only last 9 chars will be saved\n");
                token = token + (char_count - 9);
                fprintf(output, "%9.9s|", token);

            }else{ fprintf(output, "%9.9s|", token); }

            while ((token = trim(strtok(NULL,delimiter)))) {
                char_count = strlen(token);
                printf("token -> %s .... char_count -> %d\n",token, char_count);
                if(char_count > 9){
                    printf("token bigger than 9\n");
                    token = token + (char_count - 9);
                    fprintf(output, "%9.9s|", token);

                }else{ fprintf(output, "%9.9s|", token); }
            }
            fprintf(output, i == dataIndex - 1 ? "" : "\n");
        }
        fclose(output);
        printf("\n****** %s is ready to be viewed! ******\n\n\n", outFile);

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
                if( ((!strcmp(inputFileType, "csv")) || (!strcmp(inputFileType, "tc9")) || (!strcmp(inputFileType, "tl5")) || (!strcmp(inputFileType, "tr9")))
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
                    while (lastCharacter1 != '\n')//skip the remainder of my invalid command...
                        lastCharacter1 = getCommandWord(command, MAX_TOKEN);
                }
            }
            else {
                printf("\n invalid command! Your command must start either with quit or convert source.xxx destination.yyy\n");
                while (lastCharacter1 != '\n')//skip the remainder of my invalid command...
                    lastCharacter1 = getCommandWord(command, MAX_TOKEN);
            }
        }
    }

