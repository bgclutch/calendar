#include "processing.hpp"
#include "timedata.hpp"
#include "colorised_output.hpp"
#include <stdio.h>
#include <stdlib.h>

static const int LeapYearDays    = 366;
static const int RegularYearDays = 365;
static const int LeapYearFlag    = 1;
static const int RegularYearFlag = 0;
static const int WeekLen         = 7;
static const int YearLen         = 12;

static const char* MonthNames[YearLen] = {"January", "February", "March", "April", "May", "June", "July",
                                          "August", "September", "October", "November", "December"};

static const int NumOfDaysInMonth[YearLen] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static const int January   = 0;
static const int February  = 1;
static const int March     = 2;
static const int April     = 3;
static const int May       = 4;
static const int June      = 5;
static const int July      = 6;
static const int August    = 7;
static const int September = 8;
static const int October   = 9;
static const int November  = 10;
static const int December  = 11;

static const char* Monday_s    = "MON";
static const char* Tuesday_s   = "TUE";
static const char* Wednesday_s = "WED";
static const char* Thursday_s  = "THU";
static const char* Friday_s    = "FRI";
static const char* Saturday_s  = "SAT";
static const char* Sunday_s    = "SUN";

static const int Monday    = 2;
static const int Tuesday   = 3;
static const int Wednesday = 4;
static const int Thursday  = 5;
static const int Friday    = 6;
static const int Saturday  = 0;
static const int Sunday    = 1;

static const int RegYearCodes[YearLen]  = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
static const int LeapYearCodes[YearLen] = {0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
static const int WeekDaysCodes[WeekLen]  = {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

int GetMonthAndYearNums(int* CurrentMonth, int* CurrentYear){
    if (*CurrentMonth == YearLen){
           *CurrentMonth = January;
           (*CurrentYear)++;
       }
       else if (*CurrentMonth == -1){
           *CurrentMonth = December;
           (*CurrentYear)--;
       }
    return EXIT_SUCCESS;
}

const char* GetMonthName(const int CurrentMonth){
        switch (CurrentMonth){
        case January:
            return MonthNames[January];
            break;
        case February:
            return MonthNames[February];
            break;
        case March:
            return MonthNames[March];
            break;
        case April:
            return MonthNames[April];
            break;
        case May:
            return MonthNames[May];
            break;
        case June:
            return MonthNames[June];
            break;
        case July:
            return MonthNames[July];
            break;
        case August:
            return MonthNames[August];
            break;
        case September:
            return MonthNames[September];
            break;
        case October:
            return MonthNames[October];
            break;
        case November:
            return MonthNames[November];
            break;
        case December:
            return MonthNames[December];
            break;
        default:
            fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
            return nullptr;
            break;
    }
}

struct Year YearEditor(const int CurrentYear){
    struct Year RetStruct = {};
    if (CurrentYear % 4 == 0){
        RetStruct.DaysInYear = LeapYearDays;
        RetStruct.IsLeap     = LeapYearFlag;
    }
    else{
       RetStruct.DaysInYear = RegularYearDays;
       RetStruct.IsLeap     = RegularYearFlag;
    }
    RetStruct.YearNum = CurrentYear;
    RetStruct.Month_St = {};
    return RetStruct;
}

int GetDayOfWeek(const int CurDay, const int YearNum, const int MonthCode){
    int CurrentDay = (CurDay + MonthCode + (6 + YearNum % 100 + (YearNum % 100) / 4) % 7) % 7;
    return CurrentDay;
}

struct Month MonthEditor(const int CurrentMonth, const int YearNum, const int IsYearLeap){
    struct Month CreatedMonth = {};
    CreatedMonth.MonthNum = CurrentMonth;
    CreatedMonth.DaysInMonth = NumOfDaysInMonth[CurrentMonth];
    CreatedMonth.Name = GetMonthName(CurrentMonth);

    if (IsYearLeap){
        CreatedMonth.MonthCode = LeapYearCodes[CurrentMonth];
        if(CurrentMonth == February)
            CreatedMonth.DaysInMonth++;
    }
    else{
        CreatedMonth.MonthCode = RegYearCodes[CurrentMonth];
    }

    for (int i = 0; i < CreatedMonth.DaysInMonth; ++i){
        CreatedMonth.MonthDays[i].DayNumber = i + 1;
        CreatedMonth.MonthDays[i].DayOfWeek = GetDayOfWeek(i + 1, YearNum, CreatedMonth.MonthCode);
    }
    return CreatedMonth;
}


int EditOutputDate(int CurrentYear, int CurrentMonth, struct Year* CurrentYearSt){
    if (GetMonthAndYearNums(&CurrentMonth, &CurrentYear)){
            fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
            return EXIT_FAILURE;
        }

        *CurrentYearSt          = YearEditor(CurrentYear);
        CurrentYearSt->Month_St = MonthEditor(CurrentMonth, CurrentYearSt->YearNum, CurrentYearSt->IsLeap);

        if (!CurrentYearSt->Month_St.Name){
            fprintf(stderr, "\n");
            return EXIT_FAILURE;
        }

    return EXIT_SUCCESS;
}

void PrintMonth(const struct Year CurrentYear, const int CurrentDay, const int TrueMonth){
fprintf(stderr, "%s %d\n"
                    "%3s %3s %3s %3s %3s %3s %3s\n",
                    CurrentYear.Month_St.Name, CurrentYear.YearNum, Monday_s, Tuesday_s, Wednesday_s, Thursday_s,
                                                                    Friday_s, Saturday_s, Sunday_s);

    for (int day = 0; day < CurrentYear.Month_St.DaysInMonth; ++day){
        for (int weekday = 0; weekday < WeekLen; ++weekday){
            if (day == 0 && WeekDaysCodes[weekday] != CurrentYear.Month_St.MonthDays->DayOfWeek){
                fprintf(stderr, "    ");
            }
            if (WeekDaysCodes[weekday] == CurrentYear.Month_St.MonthDays[day].DayOfWeek){
                if (CurrentDay == CurrentYear.Month_St.MonthDays[day].DayNumber &&
                    CurrentYear.Month_St.MonthNum == TrueMonth){
                    fprintf(stderr, GREEN_TEXT(" %2d "), CurrentYear.Month_St.MonthDays[day].DayNumber);
                }
                else if (CurrentYear.Month_St.MonthDays[day].DayOfWeek == Saturday ||
                         CurrentYear.Month_St.MonthDays[day].DayOfWeek == Sunday){
                    fprintf(stderr, RED_TEXT(" %2d "), CurrentYear.Month_St.MonthDays[day].DayNumber);
                }
                else{
                    fprintf(stderr, " %2d ", CurrentYear.Month_St.MonthDays[day].DayNumber);
                }
                if (WeekDaysCodes[weekday] == Sunday){
                    fprintf(stderr, "\n");
                }
                break;
            }
        }
    }
    fprintf(stderr, "\n\n");
}

int OutputThreeMonth(const int CurrentYear, int CurrentMonth, const int CurrentDay,
                     struct Year* CurrentYearStruct, const int TrueMonth){
    if (EditOutputDate(CurrentYear, CurrentMonth, CurrentYearStruct)){
        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
        return EXIT_FAILURE;
    }
    PrintMonth(*CurrentYearStruct, CurrentDay, TrueMonth);
    CurrentMonth++;
    if (EditOutputDate(CurrentYear, CurrentMonth, CurrentYearStruct)){
        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
        return EXIT_FAILURE;
    }
    PrintMonth(*CurrentYearStruct, CurrentDay, TrueMonth);
    CurrentMonth++;
    if (EditOutputDate(CurrentYear, CurrentMonth, CurrentYearStruct)){
        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
        return EXIT_FAILURE;
    }
    PrintMonth(*CurrentYearStruct, CurrentDay, TrueMonth);

    return EXIT_SUCCESS;
}