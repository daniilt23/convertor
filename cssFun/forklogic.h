#ifndef FORKLOGIC_H
#define FORKLOGIC_H
#include "entrypoint.h"

void forkBin(AppContext* context, Param* param);
void forkDec(AppContext* context, Param* param);
void forkHex(AppContext* context, Param* param);

#endif // FORKLOGIC_H
