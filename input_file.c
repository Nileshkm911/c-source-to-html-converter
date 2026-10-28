/*
 * Sample test program for C Source to HTML Converter
 * Author: Nilesh Mahajan
 */

#include <stdio.h>
#include <string.h>

void show_message(void);

int main(void)
{
    /* Variable declarations */
    int count = 5;
    float pi = 3.14159f;
    char ch = 'A';
    int hex_val = 0x2F;

    printf("Hello from Source2HTML test!\n");
    printf("Value: %d, Float: %f, Char: %c, Hex: 0x%X\n", count, pi, ch, hex_val);

    // Loop example
    for (int i = 0; i < count; i++)
    {
        if (i % 2 == 0)
        {
            printf("Even index: %d\n", i);
        }
        else
        {
            printf("Odd index: %d\n", i);
        }
    }

    show_message();
    return 0;
}

void show_message(void)
{
    printf("Demonstration complete.\n");
}
