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

#include <regex>
#include "FileDate.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

/** a string that represents a day of the week */
static std::string wdayNameEn[7] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

/** a string that represents a day of the week (in german version) */
static std::string wdayNameDe[7] = {
    "Son", "Mon", "Die", "Mit", "Don", "Fre", "Sam"
};

static int getWday(std::string wday)
{
    for (int i = 0; i < 7; ++i) {
        if (wdayNameEn[i] == wday)
            return i;
    }
    for (int i = 0; i < 7; ++i) {
        if (wdayNameDe[i] == wday)
            return i;
    }
    return -1;
}

/** a string that represents a month */
static std::string monNameEn[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/** a string that represents a month (in german version) */
static std::string monNameDe[12] = {
    "Jan", "Feb", "Mär", "Apr", "Mai", "Jun",
    "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"
};

static int getMon(std::string mon)
{
    for (int i = 0; i < 12; ++i) {
        if (monNameEn[i] == mon)
            return i;
    }
    for (int i = 0; i < 12; ++i) {
        if (monNameDe[i] == mon)
            return i;
    }
    return -1;
}

FileDate::FileDate() :
    Event(),
    date()
{
    eventType = EventType::FileDate;
}

FileDate::~FileDate()
{
}

FileDate * FileDate::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL "date" REGEX_WS REGEX_WeekDay REGEX_WS REGEX_Month REGEX_WS REGEX_Date REGEX_WS REGEX_FullTime REGEX_WS REGEX_Year REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FileDate * fileDate = new FileDate;
        fileDate->date.tm_wday = getWday(match[1]);
        fileDate->date.tm_mon = getMon(match[2]);
        fileDate->date.tm_mday = std::stoul(match[3]);
        fileDate->date.tm_hour = std::stoul(match[4]);
        fileDate->date.tm_min = std::stoul(match[5]);
        fileDate->date.tm_sec = std::stoul(match[6]);
        fileDate->date.tm_hour += ((match[7] == " pm") ? 12 : 0);
        fileDate->date.tm_year = std::stoul(match[8]) - 1900;
        return fileDate;
    }

    return nullptr;
}

void FileDate::write(File & file, std::ostream & stream)
{
    stream
            << "date "
            << wdayNameEn[date.tm_wday]
            << ' '
            << monNameEn[date.tm_mon]
            << ' '
            << (date.tm_hour % 12)
            << ':'
            << date.tm_min
            << ':'
            << date.tm_sec
            << ' '
            << (date.tm_hour <= 12 ? "am" : "pm")
            << ' '
            << date.tm_year
            << endl;
}

}
}
