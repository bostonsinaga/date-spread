#include <iostream>
#include <cstdio>
#include <cmath>

bool isChANum(char ch) {
    if (ch == '0' ||
        ch == '1' ||
        ch == '2' ||
        ch == '3' ||
        ch == '4' ||
        ch == '5' ||
        ch == '6' ||
        ch == '7' ||
        ch == '8' ||
        ch == '9'
    ) {
        return true;
    }
    return false;
}

class Model {
public:
    static void normalizeDay(int &day, int &month, int &year);
    static int getMonth(int month, int year);
    static int getMonths(int month, int year);
    static int getYear(int year);

private:
    static const int days[12];
};

void Model::normalizeDay(int &day, int &month, int &year) {
    while (day > getMonth(month, year)) {
        day -= getMonth(month, year);
        month++;

        if (month >= 13) {
            month = 1;
            year++;
        }
    }

    while (day <= 0) {
        month--;

        if (month <= 0) {
            month = 12;
            year--;
        }

        day += getMonth(month, year);
    }
}

int Model::getMonth(int month, int year) {
    if (year % 4 == 0 && month == 2) {
        return 29;
    }
    else return days[month - 1];
}

int Model::getMonths(int month, int year) {
    int acc = 0;
    for (int i = 1; i < month; i++) {
        acc += getMonth(i, year);
    }
    return acc;
}

int Model::getYear(int year) {
    return year * 365 + std::floor((year - 1) / 4);
}

const int Model::days[12] = {
    31, 28, 31, 30, 31, 30, 31,
    31, 30, 31, 30, 31
};

class Date {
public:
    Date() {}

    Date(std::string dateStr) {

        int dateDex = 0;
        std::string dmy_str[] = {"", "", ""};

        for (int i = 0; i < dateStr.length(); i++) {
            if (dateStr[i] == '/' || dateStr[i] == '-') {
                if (dateDex == 2) break;
                dateDex++;
            }
            else if (isChANum(dateStr[i])) {
                dmy_str[dateDex].push_back(dateStr[i]);
            }
        }

        int dmy_int[3];

        // convert string to int
        for (int i = 0; i < 3; i++) {
            dmy_int[i] = std::stoi(dmy_str[i]);
        }

        /** Normalize Date */

        day = std::abs(dmy_int[0]);
        month = std::abs(dmy_int[1]);
        year = std::abs(dmy_int[2]);

        if (month > 12) {
            year += std::floor(month / 12);
        }

        if (month != 0) {
            month %= 12;
            if (month == 0) month = 12;
        }

        Model::normalizeDay(day, month, year);
    }

    int day = 0, month = 0, year = 0;
};

void printDaySpread(Date A, Date B, int count) {

    if (count <= 0) {
        std::cerr << "Error. Count cannot be 0 or negative." << std::endl;
        return;
    }

    if (A.year < B.year ||
        (A.year == B.year && A.month < B.month) ||
        (A.year == B.year && A.month == B.month && A.day < B.day)
    ) {
        Date buff = A;
        A = B;
        B = buff;
    }

    int aDay = A.day,
        aMonth = Model::getMonths(A.month, A.year),
        aYear = Model::getYear(A.year),
        aTotal = aDay + aMonth + aYear,
        bDay = B.day,
        bMonth = Model::getMonths(B.month, B.year),
        bYear = Model::getYear(B.year),
        bTotal = bDay + bMonth + bYear,
        differ = aTotal - bTotal;

    std::string datesSpread[count];

    if (differ > 0) {
        float changeRate = float(differ + 1) / float(count),
              dayf = B.day - changeRate;

        int day = dayf,
            month = B.month,
            year = B.year;
        
        for (int i = 0; i < count; i++) {

            dayf += changeRate;
            day = dayf;

            Model::normalizeDay(day, month, year);

            if (year > A.year ||
                (month > A.month && year == A.year) ||
                (day > A.day && month == A.month && year == A.year) ||
                (i == count - 1 && (day != A.day || month != A.month || year != A.year))
            ) {
                day = A.day;
                month = A.month;
                year = A.year;
            }

            datesSpread[i] = (
                std::to_string(day) + "/" +
                std::to_string(month) + "/" +
                std::to_string(year)
            );
        }

        std::cout << "RESULT: \n" << std::endl;

        for (int i = 0; i < count; i++) {
            std::cout << datesSpread[i] << std::endl;
        }
    }
    // no difference
    else {
        for (int i = 0; i < count; i++) {
            datesSpread[i] = (
                std::to_string(A.day) + "/" +
                std::to_string(A.month) + "/" +
                std::to_string(A.year)
            );
        }

        std::cout << "RESULT: \n" << std::endl;

        for (int i = 0; i < count; i++) {
            std::cout << datesSpread[i] << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {

    if (argc != 7) {
        std::cerr << "Input Error";
        return 0;
    }

    Date dates[2];
    int count = 0, expectedParamsCount = 3;
    std::string dateStrArr[] = {"--from", "--to"};

    for (int i = 0; i < argc; i++) {
        for (int j = 0; j < 2; j++) {
            if (argv[i] == dateStrArr[j] && i+1 < argc) {
                dates[j] = Date(std::string(argv[i+1]));
                expectedParamsCount--;
            }
        }

        if (std::string(argv[i]) == "--count" && i+1 < argc) {
            std::string numBuff = "";

            for (auto &ch : std::string(argv[i+1])) {
                if (isChANum(ch)) numBuff += ch;
            }

            if (numBuff == "") count = 0;
            else count = std::stoi(numBuff);

            expectedParamsCount--;
        }
    }

    if (expectedParamsCount == 0) {
        printDaySpread(dates[0], dates[1], count);
    }
    else std::cerr << "Input Error";

    return 0;
}

