/*
 * Project     : Source to HTML Converter
 * File        : keyword.c
 * Author      : Nilesh Mahajan
 * Description : Keyword lookup tables and identification function
 */

#include "keyword.h"
#include <string.h>

/* Standard C data type keywords */
static const char *data_keywords[] = {
    "char", "short", "int", "long", "float", "double",
    "signed", "unsigned", "void", NULL
};

/* Standard C control flow and storage class keywords */
static const char *control_keywords[] = {
    "auto", "break", "case", "const", "continue", "default",
    "do", "else", "enum", "extern", "for", "goto",
    "if", "register", "return", "sizeof", "static", "struct",
    "switch", "typedef", "union", "volatile", "while", NULL
};

/*
 * Checks whether the given word is a C data type keyword,
 * a control keyword, or an ordinary identifier.
 */
KeywordType get_keyword_type(const char *word)
{
    int i;

    /* Check data types */
    for (i = 0; data_keywords[i] != NULL; i++)
    {
        if (strcmp(word, data_keywords[i]) == 0)
        {
            return KEYWORD_DATA;
        }
    }

    /* Check control flow keywords */
    for (i = 0; control_keywords[i] != NULL; i++)
    {
        if (strcmp(word, control_keywords[i]) == 0)
        {
            return KEYWORD_CONTROL;
        }
    }

    return KEYWORD_NONE;
}
