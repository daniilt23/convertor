#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "appcontext.h"

enum Operation
{
    Transform,
    Validation,
    Clear,
    Swap
};

struct Param
{
    const char* strValue;
};

void doOperation(Operation operation, AppContext* context, Param* param);

#endif // ENTRYPOINT_H
