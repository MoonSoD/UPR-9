#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

/*
BONUS, stvrty argument reverse 
./main dictionary-en-cs.csv input.txt output.txt reverse
*/
int main(int argc, char** argv)
{
    if (argc < 4) {
        printf("Wrong parameters");
        return 1;
    }

    char* dictionary_path = argv[1];
    char* input_path = argv[2];
    char* output_path = argv[3];
    int reverse;

    if (argv[4] != NULL && strcmp(argv[4], "reverse") == 0) 
    {
        
        reverse = atoi(argv[4]) == 1;
    }

    Dictionary dictionary = load_dictionary(dictionary_path);

    translate_file_to_output(input_path, dictionary, output_path, reverse);

    free_dictionary(&dictionary);
}  