#include <ctype.h>
#include <string.h>
#include "entrypoint.h"
#include "validation.h"
#include <qdebug.h>

void validation(AppContext* context, Param* param)
{
    enum ErrorStatus result = CORRECT;
    if (strlen(param->strValue) == 0)
        result = EMPTY_LINE;
    switch(context->sysFrom)
    {
    case BIN:
        result = binValidation(param);
        break;
    case DEC:
        result = decValidation(param);
        break;
    case HEX:
        result = hexValidation(param);
        break;
    }

    context->status = result;
}

enum ErrorStatus binValidation(Param* param)
{
    enum ErrorStatus result = CORRECT;
    if (!isBinary(param->strValue))
        result = INCORRECT_DATA;
    if (!isBinaryLen(param->strValue))
        result = MAX_LEN;

    return result;
}

int isBinary(const char* str)
{
    int state = 1;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (str[i] != '0' && str[i] != '1')
        {
            state = 0;
            break;
        }
    }

    return state;
}

int isBinaryLen(const char* str)
{
    return strlen(str) < MAXBINSTRLEN;
}

enum ErrorStatus decValidation(Param* param)
{
    enum ErrorStatus result = CORRECT;
    if (!isDec(param->strValue))
        result = INCORRECT_DATA;
    char* endptr;
    long long intValue = strtoll(param->strValue, &endptr, TEN);
    if (!((param->strValue[0] == '-' || (strlen(param->strValue) == 0)) || intValue <= INT_MAX))
        result = MAX_LEN;
    if (!(strlen(param->strValue) == 0 || intValue >= INT_MIN))
        result = MIN_LEN;


    return result;
}

int isDec(const char* str)
{
    int state = 1;
    if (isdigit(str[0]) || str[0] == '-' || strlen(str) == 0)
    {
        for (size_t i = 1; i < strlen(str); i++)
        {
            if (!isdigit(str[i]))
            {
                state = 0;
                break;
            }
        }
    }
    else
        state = 0;

    return state;
}

enum ErrorStatus hexValidation(Param* param)
{
    enum ErrorStatus result = CORRECT;
    if (!isHex(param->strValue))
        result = INCORRECT_DATA;
    if (!isHexLen(param->strValue))
        result = MAX_LEN;

    return result;
}

int isHex(const char* str)
{
    int state = 1;
    for (const char* p = str; *p != '\0'; p++)
    {
        if (!isdigit(*p) && !(*p >= 'A' && *p <= 'F'))
        {
            state = 0;
            break;
        }
    }

    return state;
}

int isHexLen(const char* str)
{
    return strlen(str) < MAXHEXSTRLEN;
}
