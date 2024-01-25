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
            if (dmy_int[i] <= 0) dmy_int[i] = 1;
        }

        int unevenCtr = 0,
            unevenDays[] = {1, -2, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
            lastYears = dmy_int[2] - 1,
            leapsCount = std::floor(lastYears / 4),
            daysYears = leapsCount + 365 * lastYears,   /** product */
            lastMonths = dmy_int[1] - 1,
            lastMonthsYears = std::floor(lastMonths / 12),
            daysMonths = lastMonths * 30;   /** product */
        
        for (int i = 0; i < lastMonths; i++) {
            daysMonths += unevenDays[unevenCtr];
            unevenCtr++;
            if (unevenCtr >= 12) unevenCtr = 0;
        }

        lastYears += lastMonthsYears;
        leapsCount =- std::floor(lastYears / 4);
        daysMonths += leapsCount;

        totalDays = daysYears + daysMonths + dmy_int[0];
    }

    int totalDays = 0;
};

void printDaySpread(Date A, Date B) {

    std::cout << "Difference: " << A.totalDays - B.totalDays << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Input Error";
        return 0;
    }

    Date A = Date(std::string(argv[1]));
    Date B = Date(std::string(argv[2]));

    printDaySpread(A, B);

    return 0;
}

