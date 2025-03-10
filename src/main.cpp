#include "processing.hpp"
#include "timedata.hpp"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(){
    static const int YearOffset   = 1900;
    struct Year CurrentYearStruct = {};
    int flag = 1;

    while(flag){
        time_t CurrentTime  = time(NULL);
        tm* TmStruct        = localtime(&CurrentTime);
        int CurrentYear     = TmStruct->tm_year + YearOffset;
        const int TrueMonth = TmStruct->tm_mon;
        int CurrentMonth    = TrueMonth - 1;
        char TimeString[32] = {};
        strftime(TimeString, 32, " %H:%M", TmStruct);
        fprintf(stderr, "\n\t   %s\n\n", TimeString);

        if (OutputThreeMonth(CurrentYear, CurrentMonth, TmStruct->tm_mday, &CurrentYearStruct, TrueMonth)){
            fprintf(stderr, "Unexpected Error%s:%d\n", __FILE__, __LINE__);
            flag = 0;
        }
        sleep(60);
        system("cls");
    }

    if (flag)
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}