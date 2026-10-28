/*
 * Project     : Source to HTML Converter
 * File        : html.h
 * Author      : Nilesh Mahajan
 * Description : Header file for HTML tags, styling functions, and character writer
 */

#ifndef HTML_H
#define HTML_H

#include <stdio.h>
#include "header.h"

/* Structure/page tags */
status html_begin(FILE *fp);
status html_end(FILE *fp);

/* Helper to output character with HTML escaping */
void char_to_html(int ch, Parser *p);

/* Span wrappers for syntax coloring */
void html_line_number_begin(FILE *fp);
void html_line_number_end(FILE *fp);

void html_preprocessor_begin(FILE *fp);
void html_preprocessor_end(FILE *fp);

void html_header_begin(FILE *fp);
void html_header_end(FILE *fp);

void html_comment_begin(FILE *fp);
void html_comment_end(FILE *fp);

void html_data_keyword_begin(FILE *fp);
void html_data_keyword_end(FILE *fp);

void html_control_keyword_begin(FILE *fp);
void html_control_keyword_end(FILE *fp);

void html_number_begin(FILE *fp);
void html_number_end(FILE *fp);

void html_string_begin(FILE *fp);
void html_string_end(FILE *fp);

void html_character_begin(FILE *fp);
void html_character_end(FILE *fp);

#endif
