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

#include <iomanip>

#include <Vector/ASC/CanCommon.h>

namespace Vector {
namespace ASC {

void writeData(File & file, std::ostream & stream, std::vector<uint8_t> & data)
{
    for(uint8_t d: data) {
        switch(file.base) {
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

void writeDir(File & /*file*/, std::ostream & stream, Dir dir)
{
    switch(dir) {
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

void writeTime(File & file, std::ostream & stream, Time & time)
{
    stream
            << std::right << std::setfill(' ')
            << std::setw(5 + file.timestampPrecision)
            << std::setprecision(file.timestampPrecision)
            << std::fixed << time;
}

/** a string that represents a day of the week */
static std::string wdayNameEn[7] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

/** a string that represents a day of the week (in german version) */
static std::string wdayNameDe[7] = {
    "Son", "Mon", "Die", "Mit", "Don", "Fre", "Sam"
};

/** a string that represents a month */
static std::string monNameEn[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/** a string that represents a month (in german version) */
static std::string monNameDe[12] = {
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
        std::string wday, std::string mon, std::string mday,
        std::string hour, std::string min, std::string sec, std::string amFm,
        std::string year,
        File::Language & language,
        struct tm & date)
{
    /* parse week day */
    bool wdayFound = false;
    for(int i = 0; i < 7; ++i) {
        if (wdayNameEn[i] == wday) {
            date.tm_wday = i;
            language = File::Language::En;
            wdayFound = true;
            break;
        }
    }
    if (!wdayFound)
        for(int i = 0; i < 7; ++i) {
            if (wdayNameDe[i] == wday) {
                date.tm_wday = i;
                language = File::Language::De;
                wdayFound = true;
                break;
            }
        }

    /* parse month */
    bool monFound = false;
    for(int i = 0; i < 12; ++i) {
        if (monNameEn[i] == mon) {
            date.tm_mon = i;
            language = File::Language::En;
            monFound = true;
            break;
        }
    }
    if (!monFound)
        for(int i = 0; i < 12; ++i) {
            if (monNameDe[i] == mon) {
                date.tm_mon = i;
                language = File::Language::De;
                monFound = true;
                break;
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

void writeDate(File & file, std::ostream & ostream, struct tm & date)
{
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
