from datetime import date,  timedelta
from calendar import SATURDAY,  SUNDAY

def parse(my_date):
    d, m, y = map(int, my_date.split('/'))
    return date(y, m, d)

def days_diff(date_1, date_2):
    """date of type 15/05/1972"""
    return abs((parse(date_1) - parse(date_2)).days)

def work_days(date_1,  n):
    """
    numbers of days of work
    n -> result of function days_diff
    """
    somme = 0
    info = parse(date_1)
    for n in range(n):
        days = info + timedelta(days=n)
        if days.weekday() == SATURDAY or days.weekday() == SUNDAY:
            somme += 1
    return n - somme


DATE_1 = '25/5/1955'
DATE_2 = '28/8/2013'
n_days = days_diff(DATE_1,  DATE_2) # 21280 days
print(work_days(DATE_1, n_days)) # 15199 days working
