/*
 * Copyright (C) 2014-2015 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#include <algorithm>
#include <array>
#include <iomanip>
#include <iterator>

#include <Vector/ASC/CanCommon.h>

namespace Vector {
namespace ASC {

const std::string endl = "\r\n";

void writeData(const File & file, std::ostream & stream, const std::vector<uint8_t> & data) {
    for (uint8_t d : data) {
        switch (file.base) {
        case 10:
            stream << ' ' << std::right
                   << std::setfill(' ') << std::setw(3)
                   << std::dec << (uint16_t) d;
            break;
        case 16:
            stream << ' ' << std::right
                   << std::setfill('0') << std::setw(2)
                   << std::hex << (uint16_t) d;
            break;
        }
    }
}

void writeDir(const File & /*file*/, std::ostream & stream, const Dir dir) {
    switch (dir) {
    case Dir::Rx:
        /* format: "Rx  " */
        stream << "Rx  ";
        break;
    case Dir::Tx:
        /* format: "Tx  " */
        stream << "Tx  ";
        break;
    case Dir::TxRq:
        /* format: "TxRq" */
        stream << "TxRq";
        break;
    }
}

void writeTime(const File & file, std::ostream & stream, const Time & time) {
    stream
            << std::right << std::setfill(' ')
            << std::setw(5 + file.timestampPrecision)
            << std::setprecision(file.timestampPrecision)
            << std::fixed << time;
}

/** a string that represents a day of the week */
static const std::array<std::string, 7> wdayNameEn {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

/** a string that represents a day of the week (in german version) */
static const std::array<std::string, 7> wdayNameDe {
    "Son", "Mon", "Die", "Mit", "Don", "Fre", "Sam"
};

/** a string that represents a month */
static const std::array<std::string, 12> monNameEn = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/** a string that represents a month (in german version) */
static const std::array<std::string, 12> monNameDe = {
    "Jan", "Feb", "M\xE4r", "Apr", "Mai", "Jun",
    "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"
};

/*
 * 12/24-hour clock comparison
 * 24h   -> 12h
 * 00:00 -> 12:00 am (midnight)
 * 00:01 -> 12:01 am
 *  ...
 * 11:59 -> 11:59 am
 * 12:00 -> 12:00 pm (noon)
 * 12:01 -> 12:01 pm
 *  ...
 * 23:59 -> 11:59 pm
 * 00:00 -> 12:00 am (midnight)
 */

void readDate(
    const std::string & wday, const std::string & mon, const std::string & mday,
    const std::string & hour, const std::string & min, const std::string & sec, const std::string & amFm,
    const std::string & year,
    File::Language & language,
    struct tm & date) {
    /* parse week day */
    auto wdayIter = std::find(wdayNameEn.begin(), wdayNameEn.end(), wday);
    if (wdayIter != wdayNameEn.end()) {
        date.tm_wday = std::distance(wdayNameEn.begin(), wdayIter);
        language = File::Language::En;
    } else {
        wdayIter = std::find(wdayNameDe.begin(), wdayNameDe.end(), wday);
        if (wdayIter != wdayNameDe.end()) {
            date.tm_wday = std::distance(wdayNameDe.begin(), wdayIter);
            language = File::Language::De;
        }
    }

    /* parse month */
    auto monIter = std::find(monNameEn.begin(), monNameEn.end(), mon);
    if (monIter != monNameEn.end()) {
        date.tm_mon = std::distance(monNameEn.begin(), monIter);
        language = File::Language::En;
    } else {
        monIter = std::find(monNameDe.begin(), monNameDe.end(), mon);
        if (monIter != monNameDe.end()) {
            date.tm_mon = std::distance(monNameDe.begin(), monIter);
            language = File::Language::De;
        }
    }

    /* parse the rest */
    date.tm_mday = std::stoul(mday);
    date.tm_hour = std::stoul(hour);
    date.tm_min = std::stoul(min);
    date.tm_sec = std::stoul(sec);

    /* 12/24-hour clock handling */
    if (amFm == " am") {
        language = File::Language::En;
        /* midnight */
        if (date.tm_hour == 12)
            date.tm_hour = 0;
    } else if (amFm == " pm") {
        language = File::Language::En;
        /* noon stays, but all others are +12 */
        if (date.tm_hour != 12)
            date.tm_hour += 12;
    } else
        language = File::Language::De;

    /* parse the rest */
    date.tm_year = std::stoul(year) - 1900;
}

void writeDate(const File & file, std::ostream & ostream, const struct tm & date) {
    uint16_t hour = date.tm_hour;

    /* 12/24-hour clock handling */
    std::string amFm;
    if (file.language == File::Language::En) {
        /* am/pm */
        if (hour < 12)
            amFm = " am";
        else
            amFm = " pm";

        /* hour */
        hour %= 12;
        /* noon/midnight */
        if (hour == 0)
            hour = 12;
    }

    /* write output */
    ostream
            << (file.language == File::Language::En ? wdayNameEn[date.tm_wday] : wdayNameDe[date.tm_wday])
            << ' ' << (file.language == File::Language::En ? monNameEn[date.tm_mon] : monNameDe[date.tm_mon])
            << ' ' << std::dec << date.tm_mday
            << ' ' << std::setfill('0') << std::setw(2) << std::dec << hour
            << ':' << std::setfill('0') << std::setw(2) << std::dec << date.tm_min
            << ':' << std::setfill('0') << std::setw(2) << std::dec << date.tm_sec
            << amFm
            << ' ' << std::dec << date.tm_year + 1900;
}

}
}
