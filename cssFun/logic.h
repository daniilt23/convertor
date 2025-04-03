#ifndef LOGIC_H
#define LOGIC_H

#include "entrypoint.h"

void pickAction(AppContext* context, Param* param);
void initialization(AppContext* context);
void swap(AppContext* context, Param* param);
void transformToBinFromDec(AppContext* context, Param* param);
void transformToHexFromDec(AppContext* context, Param* param);
void transformToDecFromBin(AppContext* context, Param* param);
void transformToDecFromHex(AppContext* context, Param* param);
void transfromFromNegDecToBin(char* binValue);
char* removeLeadingZeros(char* binValue);

#endif // LOGIC_H
