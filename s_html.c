/*
 * Project     : Source to HTML Converter
 * File        : s_html.c
 * Author      : Nilesh Mahajan
 * Description : Main parsing loop and default idle state transitions
 */

#include "header.h"
#include "s_html.h"
#include "html.h"

/*
 * Default state handler (STATE_IDLE)
 * Identifies the beginning of new tokens and switches state accordingly.
 */
ParserState state_idle(int ch, Parser *p)
{
    /* Preprocessor directive check */
    if (ch == '#')
    {
        html_preprocessor_begin(p->html);
        char_to_html(ch, p);
        return STATE_PREPROCESSOR;
    }

    /* String literal start */
    else if (ch == '\"')
    {
        html_string_begin(p->html);
        char_to_html(ch, p);
        return STATE_STRING;
    }

    /* Comment or division operator */
    else if (ch == '/')
    {
        p->prev = ch;
        int next_ch = fgetc(p->src);

        if (next_ch == '/')
        {
            html_comment_begin(p->html);
            char_to_html(p->prev, p);
            char_to_html(next_ch, p);
            return STATE_SINGLE_COMMENT;
        }
        else if (next_ch == '*')
        {
            html_comment_begin(p->html);
            char_to_html(p->prev, p);
            char_to_html(next_ch, p);
            return STATE_MULTI_COMMENT;
        }

        /* Not a comment, put back character and emit '/' */
        ungetc(next_ch, p->src);
        char_to_html(p->prev, p);
        return STATE_IDLE;
    }

    /* Word token (identifier or keyword) */
    else if (isalpha(ch) || ch == '_')
    {
        p->index = 0;
        p->word[(p->index)++] = ch;
        return STATE_WORD;
    }

    /* Numeric constant */
    else if (isdigit(ch))
    {
        p->index = 0;
        p->has_dot = 0;
        p->is_hex = 0;
        p->word[(p->index)++] = ch;
        return STATE_NUMBER;
    }

    /* Character literal start */
    else if (ch == '\'')
    {
        html_character_begin(p->html);
        char_to_html(ch, p);
        return STATE_CHARACTER;
    }

    /* Standard punctuation, operator, or whitespace */
    char_to_html(ch, p);
    return STATE_IDLE;
}

/*
 * Main parsing function: reads source character by character and
 * transitions through states in the finite state machine.
 */
status s_html(Parser *parser)
{
    int ch;

    /* Initialize parser state and line numbering */
    parser->state = STATE_IDLE;
    parser->current_line = 1;

    /* Print first line number gutter */
    html_line_number_begin(parser->html);
    fprintf(parser->html, "%3d  ", parser->current_line);
    html_line_number_end(parser->html);

    /* Read character-by-character until end of file */
    while ((ch = fgetc(parser->src)) != EOF)
    {
        switch (parser->state)
        {
            case STATE_IDLE:
                parser->state = state_idle(ch, parser);
                break;

            case STATE_WORD:
                parser->state = state_word(ch, parser);
                break;

            case STATE_NUMBER:
                parser->state = state_number(ch, parser);
                break;

            case STATE_STRING:
                parser->state = state_string(ch, parser);
                break;

            case STATE_CHARACTER:
                parser->state = state_character(ch, parser);
                break;

            case STATE_SINGLE_COMMENT:
                parser->state = state_single_line_comment(ch, parser);
                break;

            case STATE_MULTI_COMMENT:
                parser->state = state_multi_line_comment(ch, parser);
                break;

            case STATE_PREPROCESSOR:
                parser->state = state_preprocessor(ch, parser);
                break;

            case STATE_HEADER:
                parser->state = state_header(ch, parser);
                break;

            default:
                parser->state = STATE_IDLE;
                break;
        }
    }

    return SUCCESS;
}
