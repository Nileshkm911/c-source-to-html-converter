/*
 * Project     : Source to HTML Converter
 * File        : parser.c
 * Author      : Nilesh Mahajan
 * Description : State machine handler functions for preprocessor, comments, words, numbers, strings
 */

#include "header.h"
#include "s_html.h"
#include "html.h"
#include "keyword.h"

/*
 * Preprocessor state handler (#include, #define, etc.)
 */
ParserState state_preprocessor(int ch, Parser *p)
{
    if (ch == '<')
    {
        html_preprocessor_end(p->html);
        html_header_begin(p->html);
        char_to_html(ch, p);
        p->header_delimiter = '>';
        return STATE_HEADER;
    }
    else if (ch == '\"')
    {
        html_preprocessor_end(p->html);
        html_header_begin(p->html);
        char_to_html(ch, p);
        p->header_delimiter = '\"';
        return STATE_HEADER;
    }

    char_to_html(ch, p);
    return STATE_PREPROCESSOR;
}

/*
 * Header include filename state handler (<stdio.h> or "myheader.h")
 */
ParserState state_header(int ch, Parser *p)
{
    char_to_html(ch, p);

    if (ch == p->header_delimiter)
    {
        html_header_end(p->html);
        return STATE_IDLE;
    }

    return STATE_HEADER;
}

/*
 * Single-line comment state handler (// ...)
 */
ParserState state_single_line_comment(int ch, Parser *p)
{
    if (ch == '\n')
    {
        html_comment_end(p->html);
        ungetc(ch, p->src);
        return STATE_IDLE;
    }

    char_to_html(ch, p);
    return STATE_SINGLE_COMMENT;
}

/*
 * Multi-line comment state handler
 */
ParserState state_multi_line_comment(int ch, Parser *p)
{
    char_to_html(ch, p);

    if (p->prev == '*' && ch == '/')
    {
        html_comment_end(p->html);
        return STATE_IDLE;
    }

    p->prev = ch;
    return STATE_MULTI_COMMENT;
}

/*
 * Identifier / keyword word state handler
 */
ParserState state_word(int ch, Parser *p)
{
    if (isalnum(ch) || ch == '_')
    {
        if (p->index < MAX_WORD_LEN - 1)
        {
            p->word[(p->index)++] = ch;
            return STATE_WORD;
        }
    }

    p->word[p->index] = '\0';

    KeywordType type = get_keyword_type(p->word);
    switch (type)
    {
        case KEYWORD_DATA:
            html_data_keyword_begin(p->html);
            fprintf(p->html, "%s", p->word);
            html_data_keyword_end(p->html);
            break;

        case KEYWORD_CONTROL:
            html_control_keyword_begin(p->html);
            fprintf(p->html, "%s", p->word);
            html_control_keyword_end(p->html);
            break;

        default:
            fprintf(p->html, "%s", p->word);
            break;
    }

    ungetc(ch, p->src);
    return STATE_IDLE;
}

/*
 * Helper for collecting numeric characters
 */
static void numeric_literal(int ch, Parser *p)
{
    if (p->index < MAX_WORD_LEN - 1)
    {
        p->word[p->index++] = ch;
    }
}

/*
 * Numeric constant state handler (integers, hex, floats)
 */
ParserState state_number(int ch, Parser *p)
{
    /* Decimal digits */
    if (isdigit((unsigned char)ch))
    {
        numeric_literal(ch, p);
        return STATE_NUMBER;
    }

    /* Hexadecimal prefix '0x' or '0X' */
    if ((ch == 'x' || ch == 'X') && p->index == 1 && p->word[0] == '0')
    {
        p->is_hex = 1;
        numeric_literal(ch, p);
        return STATE_NUMBER;
    }

    /* Hexadecimal digits */
    if (p->is_hex && isxdigit((unsigned char)ch))
    {
        numeric_literal(ch, p);
        return STATE_NUMBER;
    }

    /* Floating point dot */
    if (ch == '.' && !p->is_hex && !p->has_dot)
    {
        p->has_dot = 1;
        numeric_literal(ch, p);
        return STATE_NUMBER;
    }

    p->word[p->index] = '\0';

    html_number_begin(p->html);
    fprintf(p->html, "%s", p->word);
    html_number_end(p->html);

    ungetc(ch, p->src);
    return STATE_IDLE;
}

/*
 * Character literal state handler ('a', '\n')
 */
ParserState state_character(int ch, Parser *p)
{
    char_to_html(ch, p);

    if (ch == '\'')
    {
        html_character_end(p->html);
        return STATE_IDLE;
    }

    return STATE_CHARACTER;
}

/*
 * String literal state handler ("...")
 */
ParserState state_string(int ch, Parser *p)
{
    char_to_html(ch, p);

    if (ch == '\"')
    {
        html_string_end(p->html);
        return STATE_IDLE;
    }

    return STATE_STRING;
}
