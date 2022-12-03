#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "dictionary.h"
 
void trim_newline(char* str)
{
    int i;
    for (i = 0; str[i] != '\n'; i++)
    {
        // no need to trim
        if (str[i] == '\0')
            return;
    }

    str[i] = '\0';
}

char* translate_word(char* word_str, Dictionary dictionary, bool reverse) 
{
    for (size_t i = 0; i < dictionary.pos; i++) 
    {
        DictionaryEntry entry = dictionary.entries[i];

        if (reverse) {
            if (strcmp(word_str, entry.old_str) == 0)
            {
                return entry.new_str;
            }
        } else {
            if (strcmp(word_str, entry.new_str) == 0)
            {
                return entry.old_str;
            }
        }
      
    }

    return "<unknown>";
}

void translate_line_to_output(char* line_str, Dictionary dictionary, char* output_path, bool reverse)
{
    FILE* output_file = fopen(output_path, "a+");

    if (output_file == NULL) {
        printf("Could not open output file");
        exit(1);
    }

    char *token = strtok(line_str, " \r\n\0");
    if (token != NULL) {
        do 
        {   
            char* translated_token = translate_word(token, dictionary, reverse);

            fprintf(output_file, "%s ", translated_token);
        } while ((token = strtok(NULL, " \r\n\0")) != NULL);

        fprintf(output_file, "\n");
    }


    fclose(output_file);
}

void translate_file_to_output(char* input_path, Dictionary dictionary, char* output_path, bool reverse)
{
    FILE* input_file = fopen(input_path, "r");

    if (input_file == NULL) {
        printf("Could not open input file");
        exit(1);
    }

    char read_line[255];

    while(fgets(read_line, 255, input_file) != NULL)
    {
        translate_line_to_output(read_line, dictionary, output_path, reverse);
    }

    fclose(input_file);
}


void append_entry_to_dictionary(Dictionary* dictionary, DictionaryEntry entry) 
{
    if (dictionary->length < dictionary->pos + 1) {
        dictionary->entries = realloc(dictionary->entries, sizeof(DictionaryEntry) * (dictionary->length * 2));
        dictionary->length *= 2;

        assert(dictionary->entries);
    }

    dictionary->entries[dictionary->pos] = entry;
    dictionary->pos += 1;

}

Dictionary load_dictionary(char* dictionary_path) 
{
    FILE* file = fopen(dictionary_path, "rb");
    
    Dictionary dictionary;
    
    dictionary.length = 2;
    dictionary.pos = 0;
    dictionary.entries = malloc(sizeof(DictionaryEntry) * 2);
    
    if (file == NULL) {
        printf("Could not load dictionary");
        exit(1);
    }

    char read_line[255]; 
    size_t line_index = 0;

    while(fgets(read_line, 255, file) != NULL)
    {
        char* left = strdup(strtok(read_line, ", \r\n\0"));
        char* right = strdup(strtok(NULL, ", \r\n\0"));

        append_entry_to_dictionary(&dictionary, (DictionaryEntry) {left, right});

        line_index++;
    }

    return dictionary;    
}

void free_dictionary(Dictionary* dictionary)
{
    for (size_t i = 0; i < dictionary->pos; i++) {
        DictionaryEntry entry = dictionary->entries[i];

        free(entry.new_str);
        free(entry.old_str);
    }

    free(dictionary->entries);
}

