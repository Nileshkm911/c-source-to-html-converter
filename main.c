/*
 * Project     : Source to HTML Converter
 * File        : main.c
 * Author      : Nilesh Mahajan
 * Description : Program entry point and execution coordinator
 */

#include "header.h"
#include "html.h"

int main(int argc, char *argv[])
{
    Parser parser;

    /* Validate user command-line arguments */
    if (evaluate_arguments(argc, argv) != SUCCESS)
    {
        return 1;
    }

    /* Open input C file and output HTML file */
    if (open_file(argv, &parser) != SUCCESS)
    {
        return 1;
    }

    printf("Starting conversion of '%s' to '%s'...\n", argv[1], argv[2]);

    /* Write HTML page header and styles */
    html_begin(parser.html);

    /* Run state machine parser to convert source code */
    s_html(&parser);

    /* Close HTML tags */
    html_end(parser.html);

    /* Close all open file descriptors */
    fclose(parser.src);
    fclose(parser.html);

    printf("HTML file generated successfully: %s\n", argv[2]);

    return 0;
}
