#ifndef APPCONTEXT_H
#define APPCONTEXT_H

enum Sys
{
    BIN = 2,
    DEC = 10,
    HEX = 16,
};

enum ErrorStatus
{
    CORRECT,
    INCORRECT_DATA,
    MIN_LEN,
    MAX_LEN,
    EMPTY_LINE
};

enum
{
    TWO = 2
};

enum
{
    MAXHEXSTRLEN = 9,
    MAXDECSTRLEN = 11,
    MAXBINSTRLEN = 33
};

struct AppContext
{
    enum Sys sysFrom;
    enum Sys sysTo;
    const char* newValue;
    enum ErrorStatus status;
};

#endif // APPCONTEXT_H
