#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "inputs.h"
int getInt(int* a)
{
    int A;
    do
    {

        A = scanf("%d", a);
        if (A < 0)
        {
            return 0;
        }
        if (A == 0)
        {
            printf("Try again:\n");
            scanf("%*s");
        }

    } while (A == 0);
    return 1;
}
int getReal(double* p)
{
    double B;
    do
    {

        B = scanf("%10lf", p);
        if (B < 0)
        {
            return 0;
        }
        if (B == 0)
        {
            printf("Try again!\n");
            scanf("%*s");
        }

    } while (B == 0);
    return 1;
}
char* get_str()
{
    char buf[101] = { 0 };
    char* p = NULL;
    int n = 0;
    int len = 0;
    do
    {
        n = scanf("%100[^\n]", buf);
        if (n < 0)
        {
            if (!p)
            {
                printf("\nEnd of file occured!\n");
                return NULL;
            }
        }
        else if (n > 0)
        {
            char* tmp = p;
            p = (char*)realloc(p, len + strlen(buf) + 1);
            if (!p)
            {
                free(tmp);
                return NULL;
            }
            memcpy(p + len, buf, strlen(buf));
            len += strlen(buf);
        }
        else
        {
            scanf("%*c");
        }

    } while (n > 0);

    if (len > 0)
    {
        p[len] = '\0';
    }
    else
    {
        p = (char*)calloc(1, sizeof(char));
    }
    return p;
}
int input_str(char** str, const char* msg)
{
    const char* pr = "";
    do
    {
        printf("%s\n%s ", pr, msg);
        *str = get_str();
        if (!*str)
            return 1;
        pr = "Error! Try again!";
    } while (!str);
    return 0;
}
int inputI(int* turn, const char* msg)
{
    const char* t = " ";
    do
    {
        printf("%s\n%s ", t, msg);
        t = "Out of range!";
        if (getInt(turn) == 0)
        {
            return 1;
        }

    } while (turn < 0);
    return 0;
}
int inputR(double* turn, const char* msg)
{
    const char* t = " ";
    do
    {
        printf("%s\n%s ", t, msg);
        t = "Out of range!";
        if (getReal(turn) == 0)
        {
            return 1;
        }

    } while (turn < 0);
    return 0;
}
