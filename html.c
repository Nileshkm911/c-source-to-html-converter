/*
 * Project     : Source to HTML Converter
 * File        : html.c
 * Author      : Nilesh Mahajan
 * Description : HTML generation, page framing, CSS styling, and character escaping
 */

#include "header.h"
#include "html.h"

/*
 * Writes the HTML document header, modern dark theme styling,
 * and starts the preformatted code block.
 */
status html_begin(FILE *fp)
{
    fprintf(fp,
            "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "<meta charset=\"UTF-8\">\n"
            "<title>C Source to HTML - Nilesh Mahajan</title>\n"
            "<style>\n"
            "body {\n"
            "    background: #181818;\n"
            "    color: #e0e0e0;\n"
            "    font-family: 'Consolas', 'Courier New', monospace;\n"
            "    font-size: 15px;\n"
            "    padding: 16px;\n"
            "}\n"
            "pre {\n"
            "    white-space: pre-wrap;\n"
            "    line-height: 1.4;\n"
            "}\n"
            ".lineno  { color: #6e7681; user-select: none; margin-right: 12px; }\n"
            ".preproc { color: #d19a66; font-weight: bold; }\n"
            ".header  { color: #98c379; }\n"
            ".comment { color: #7f848e; font-style: italic; }\n"
            ".data    { color: #e5c07b; font-weight: bold; }\n"
            ".ctrl    { color: #c678dd; font-weight: bold; }\n"
            ".num     { color: #61afef; }\n"
            ".str     { color: #98c379; }\n"
            ".ch      { color: #56b6c2; }\n"
            "</style>\n"
            "</head>\n"
            "<body>\n"
            "<pre>\n");

    return SUCCESS;
}

/*
 * Closes the preformatted block, body, and html tags.
 */
status html_end(FILE *fp)
{
    fprintf(fp,
            "</pre>\n"
            "</body>\n"
            "</html>\n");

    return SUCCESS;
}

/*
 * Writes a character to the HTML output, escaping '<', '>', '&'
 * and printing line numbers on newline.
 */
void char_to_html(int ch, Parser *p)
{
    FILE *fp = p->html;

    if (ch == '<')
    {
        fprintf(fp, "&lt;");
    }
    else if (ch == '>')
    {
        fprintf(fp, "&gt;");
    }
    else if (ch == '&')
    {
        fprintf(fp, "&amp;");
    }
    else if (ch == '\n')
    {
        fprintf(fp, "\n");
        (p->current_line)++;

        html_line_number_begin(p->html);
        fprintf(fp, "%3d  ", p->current_line);
        html_line_number_end(p->html);
    }
    else
    {
        fputc(ch, fp);
    }
}

/* Helper functions for styling spans */
void html_line_number_begin(FILE *fp)
{
    fprintf(fp, "<span class=\"lineno\">");
}
void html_line_number_end(FILE *fp)
{
    fprintf(fp, "</span>");
}

void html_preprocessor_begin(FILE *fp)
{
    fprintf(fp, "<span class=\"preproc\">");
}
void html_preprocessor_end(FILE *fp)
{
    fprintf(fp, "</span>");
}

void html_header_begin(FILE *fp)
{
    fprintf(fp, "<span class=\"header\">");
}
void html_header_end(FILE *fp)
{
    fprintf(fp, "</span>");
}

void html_comment_begin(FILE *fp)
{
    fprintf(fp, "<span class=\"comment\">");
}
void html_comment_end(FILE *fp)
{
    fprintf(fp, "</span>");
}

void html_data_keyword_begin(FILE *fp)
{
    fprintf(fp, "<span class=\"data\">");
}
void html_data_keyword_end(FILE *fp)
{
    fprintf(fp, "</span>");
}

void html_control_keyword_begin(FILE *fp)
{
    fprintf(fp, "<span class=\"ctrl\">");
}
void html_control_keyword_end(FILE *fp)
{
    fprintf(fp, "</span>");
}

void html_number_begin(FILE *fp)
{
    fprintf(fp, "<span class=\"num\">");
}
void html_number_end(FILE *fp)
{
    fprintf(fp, "</span>");
}

void html_string_begin(FILE *fp)
{
    fprintf(fp, "<span class=\"str\">");
}
void html_string_end(FILE *fp)
{
    fprintf(fp, "</span>");
}

void html_character_begin(FILE *fp)
{
    fprintf(fp, "<span class=\"ch\">");
}
void html_character_end(FILE *fp)
{
    fprintf(fp, "</span>");
}
