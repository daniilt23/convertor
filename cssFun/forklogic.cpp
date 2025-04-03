#include <stdlib.h>
#include "forklogic.h"
#include "logic.h"

void forkBin(AppContext* context, Param* param)
{
    if (context->sysTo == DEC)
        transformToDecFromBin(context, param);
    else if (context->sysTo == HEX)
    {
        transformToDecFromBin(context, param);
        transformToHexFromDec(context, param);
    }
}

void forkHex(AppContext* context, Param* param)
{
    if (context->sysTo == DEC)
        transformToDecFromHex(context, param);
    else if (context->sysTo == BIN)
    {
        transformToDecFromHex(context, param);
        transformToBinFromDec(context, param);
    }
}

void forkDec(AppContext* context, Param* param)
{
    switch(context->sysTo)
    {
    case BIN:
        transformToBinFromDec(context, param);
        break;
    case HEX:
        transformToHexFromDec(context, param);
        break;
    }
}
