#pragma once

typedef struct {
    char* old_str;
    char* new_str;
} DictionaryEntry;

typedef struct {
    DictionaryEntry* entries;     
    size_t length;
    size_t pos; 
} Dictionary;   


void trim_newline(char *str);

char* translate_word(char* word_str, Dictionary dictionary, bool reverse);

void translate_line_to_output(char* line_str, Dictionary dictionary, char* output_path, bool reverse);

void translate_file_to_output(char* input_path, Dictionary dictionary, char* output_path, bool reverse);

void append_entry_to_dictionary(Dictionary* dictionary, DictionaryEntry entry);

Dictionary load_dictionary(char* dictionary_path);

void free_dictionary(Dictionary* dictionary);