#ifndef TIMEDATA_H_
#define TIMEDATA_H_

const int MAXMONTHSIZE = 31;

struct Day{
    int DayNumber;
    int DayOfWeek;
};

struct Month{
    const char* Name;
    int MonthNum;
    int DaysInMonth;
    struct Day MonthDays[MAXMONTHSIZE];
    int MonthCode;
};

struct Year{
    int DaysInYear;
    int IsLeap;
    int YearNum;
    struct Month Month_St;
};


#endif // TIMEDATA_H_