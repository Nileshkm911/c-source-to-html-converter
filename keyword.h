/*
 * Project     : Source to HTML Converter
 * File        : keyword.h
 * Author      : Nilesh Mahajan
 * Description : Header file for C language keyword types and declarations
 */

#ifndef KEYWORD_H
#define KEYWORD_H

/* Classification of C keywords */
typedef enum {
    KEYWORD_NONE,
    KEYWORD_DATA,
    KEYWORD_CONTROL
} KeywordType;

/* Function to check if a word is a C keyword and return its category */
KeywordType get_keyword_type(const char *word);

#endif
