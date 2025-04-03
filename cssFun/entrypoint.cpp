#include "entrypoint.h"
#include "logic.h"
#include "validation.h"

void doOperation(Operation operation, AppContext* context, Param* param)
{
    switch(operation)
    {
    case Transform:
        pickAction(context, param);
        break;
    case Clear:
        initialization(context);
        break;
    case Validation:
        validation(context, param);
        break;
    case Swap:
        swap(context, param);
        break;
    }
}
