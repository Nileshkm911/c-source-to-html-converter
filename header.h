/*
 * Project     : Source to HTML Converter
 * File        : header.h
 * Author      : Nilesh Mahajan
 * Description : Main header file with parser structures, states, and prototypes
 */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 128

/* Enum for different states of the parser state machine */
typedef enum {
    STATE_IDLE,
    STATE_WORD,
    STATE_NUMBER,
    STATE_STRING,
    STATE_CHARACTER,
    STATE_SINGLE_COMMENT,
    STATE_MULTI_COMMENT,
    STATE_PREPROCESSOR,
    STATE_HEADER
} ParserState;

/* Structure to maintain parser context and file streams */
typedef struct {
    FILE *src;                 /* input .c file pointer */
    FILE *html;                /* output .html file pointer */
    ParserState state;         /* current state of parser */

    char word[MAX_WORD_LEN];   /* buffer for tokens/keywords/numbers */
    int index;                 /* current index in word buffer */
    int prev;                  /* previous character helper */

    int has_dot;               /* flag for floating numbers */
    int is_hex;                /* flag for hexadecimal numbers */

    int header_delimiter;      /* '>' or '"' delimiter for include headers */
    int current_line;          /* line number counter */
} Parser;

/* Status enum for error handling */
typedef enum {
    FAILURE = 0,
    SUCCESS = 1
} status;

/* Function declarations */
status evaluate_arguments(int argc, char *argv[]);
status open_file(char *argv[], Parser *parser);
status s_html(Parser *parser);

#endif
