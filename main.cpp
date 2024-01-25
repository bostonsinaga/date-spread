#include <iostream>
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

class Date {
public:
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

        // month boundary
        if (dmy_int[1] > 12) {
            dmy_int[2] += std::floor(dmy_int[1] / 12);
            int rest = dmy_int[1] % 12;

            if (rest == 0) dmy_int[1] = 12;
            else dmy_int[1] = rest;
        }

        // day boundary
        if (dmy_int[0] > model[dmy_int[1]]) {
            dmy_int[0];
        }

        // year
        if (dmy_int[2] % 4 == 0) {
            model[1] = 29;
        }
    }

    int day, month, year;

    int model[] = {
        31, 28, 31, 30, 31, 30, 31,
        31, 30, 31, 30, 31
    };
};

void printDaySpread(Date A, Date B) {

    if (A.year < B.year) {
        Date buff = A;
        A = B;
        B = buff;
    }

    int dayAccumulation = A.month A.day;

    for (int i = 0; i < 12; i++) {
        
    }
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Input Error";
        return 0;
    }

    Date A = Date(std::string(argv[1]));
    Date B = Date(std::string(argv[2]));

    return 0;
}

