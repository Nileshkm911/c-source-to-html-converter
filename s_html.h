/*
 * Project     : Source to HTML Converter
 * File        : s_html.h
 * Author      : Nilesh Mahajan
 * Description : Header for main parsing engine and state handlers
 */

#ifndef S_HTML_H
#define S_HTML_H

#include "header.h"

ParserState state_idle(int ch, Parser *p);
ParserState state_preprocessor(int ch, Parser *p);
ParserState state_header(int ch, Parser *p);
ParserState state_single_line_comment(int ch, Parser *p);
ParserState state_multi_line_comment(int ch, Parser *p);
ParserState state_word(int ch, Parser *p);
ParserState state_number(int ch, Parser *p);
ParserState state_character(int ch, Parser *p);
ParserState state_string(int ch, Parser *p);

#endif
