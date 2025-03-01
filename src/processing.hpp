#ifndef PROCESSING_H_

int GetMonthAndYearNums(int*, int*);
const char* GetMonthName(const int);
struct Year YearEditor(const int);
struct Month MonthEditor(const int, const int, const int);
int GetDayOfWeek(const int, const int, const int);
void PrintMonth(const struct Year, const int, const int);
int EditOutputDate(int, int, struct Year*);
int OutputThreeMonth(const int, int, const int, struct Year*, const int);

#endif // PROCESSING_H_