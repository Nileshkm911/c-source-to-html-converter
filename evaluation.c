/*
 * Project     : Source to HTML Converter
 * File        : evaluation.c
 * Author      : Nilesh Mahajan
 * Description : Argument validation and file handling
 */

#include "header.h"

/*
 * Validates command line arguments.
 * Usage: ./source2html <input.c> <output.html>
 */
status evaluate_arguments(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("\nError: Invalid number of arguments\n");
        printf("Usage: %s <input.c> <output.html>\n\n", argv[0]);
        return FAILURE;
    }

    /* Check input filename */
    char *c_ext = strrchr(argv[1], '.');
    if (c_ext == NULL || strcmp(c_ext, ".c") != 0)
    {
        printf("\nError: Input file must be a .c source file\n");
        return FAILURE;
    }

    /* Check output filename */
    char *html_ext = strrchr(argv[2], '.');
    if (html_ext == NULL || strcmp(html_ext, ".html") != 0)
    {
        printf("\nError: Output file must have a .html extension\n");
        return FAILURE;
    }

    return SUCCESS;
}

/*
 * Opens the input source file in read mode and output file in write mode.
 */
status open_file(char *argv[], Parser *parser)
{
    parser->src = fopen(argv[1], "r");
    if (parser->src == NULL)
    {
        printf("\nError: Unable to open input file '%s'\n", argv[1]);
        return FAILURE;
    }

    parser->html = fopen(argv[2], "w");
    if (parser->html == NULL)
    {
        printf("\nError: Unable to create output file '%s'\n", argv[2]);
        fclose(parser->src);
        return FAILURE;
    }

    return SUCCESS;
}
