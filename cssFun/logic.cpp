#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "entrypoint.h"
#include "logic.h"
#include "forklogic.h"
#include "memory.h"

void pickAction(AppContext* context, Param* param)
{
    if (context->sysFrom == context->sysTo)
        context->newValue = param->strValue;
    else
    {
        switch(context->sysFrom)
        {
        case BIN:
            forkBin(context, param);
            break;
        case HEX:
            forkHex(context, param);
            break;
        case DEC:
            forkDec(context, param);
            break;
        }
    }
}

void initialization(AppContext* context)
{
    context->newValue = "";
}

void transformToBinFromDec(AppContext* context, Param* param)
{
    char* binValue = allocateMemory(MAXBINSTRLEN);
    for (size_t i = 0; i < MAXBINSTRLEN - 1; i++)
        binValue[i] = '0';
    binValue[MAXBINSTRLEN - 1] = '\0';
    int tempDec = abs(atoi(param->strValue));
    for (int i = MAXBINSTRLEN - TWO; i >= 0; i--)
    {
        binValue[i] = (tempDec % TWO) + '0';
        tempDec /= TWO;
    }
    if (atoi(param->strValue) > 0)
    {
        char* binValue2 = removeLeadingZeros(binValue);
        context->newValue = binValue2;
    }
    if (atoi(param->strValue) < 0)
    {
        transfromFromNegDecToBin(binValue);
        context->newValue = strdup(binValue);
    }
    free(binValue);
}

char* removeLeadingZeros(char* binValue)
{
    char* firstNonZero = binValue;
    while (*firstNonZero == '0' && *firstNonZero != '\0')
        firstNonZero++;

    char* trimmedValue = strdup(firstNonZero);

    return trimmedValue;
}

void transfromFromNegDecToBin(char* binValue)
{
    for (size_t i = 0; i < MAXBINSTRLEN - 1; i++)
    {
        if (binValue[i] == '0')
            binValue[i] = '1';
        else
            binValue[i] = '0';
    }
    int carry = 1;
    for (size_t i = MAXBINSTRLEN - TWO; i >= 0; i--)
    {
        if (carry == 1 && binValue[i] == '1')
            binValue[i] = '0';
        else if (carry == 1 && binValue[i] == '0')
        {
            binValue[i] = '1';
            break;
        }
    }
}

void transformToHexFromDec(AppContext* context, Param* param)
{
    char* hexValue = allocateMemory(MAXHEXSTRLEN);
    if (atoi(param->strValue) > 0)
        sprintf(hexValue, "%X", atoi(param->strValue));
    else
    {
        transformToBinFromDec(context, param);
        param->strValue = context->newValue;
        transformToDecFromBin(context, param);
        sprintf(hexValue, "%X", atoi(context->newValue));
    }
    context->newValue = strdup(hexValue);
    free(hexValue);
}

void transformToDecFromBin(AppContext* context, Param* param)
{
    char* decValue = allocateMemory(MAXDECSTRLEN);
    int newValue = 0;
    size_t len = strlen(param->strValue);
    for (size_t i = 0; i < len; i++)
    {
        if (param->strValue[len - i - 1] == '1')
            newValue += (1 << i);
    }
    sprintf(decValue, "%d", newValue);

    context->newValue = strdup(decValue);
    free(decValue);
}

void transformToDecFromHex(AppContext* context, Param* param)
{
    char* endptr;
    char* strValue = allocateMemory(MAXDECSTRLEN);
    int number = strtoul(param->strValue, &endptr, 16);
    if (number < 0)
        number -= (1LL << 32);
    sprintf(strValue, "%d", number);

    context->newValue = strdup(strValue);
    free(strValue);
}

void swap(AppContext* context, Param* param)
{
    const char* temp = param->strValue;
    param->strValue = context->newValue;
    context->newValue = temp;

    enum Sys tempS = context->sysFrom;
    context->sysFrom = context->sysTo;
    context->sysTo = tempS;
}
