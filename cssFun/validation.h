#ifndef VALIDATION_H
#define VALIDATION_H
#include "entrypoint.h"

enum
{
    TEN = 10,
};

void validation(AppContext* context, Param* param);
enum ErrorStatus binValidation(Param* param);
enum ErrorStatus decValidation(Param* param);
enum ErrorStatus hexValidation(Param* param);
int isBinary(const char* str);
int isDec(const char* str);
int isHex(const char* str);
int isBinaryLen(const char* str);
int isHexLen(const char* str);

#endif // VALIDATION_H
