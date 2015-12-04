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
#include <regex>
#include "CanCommon.h"
#include "CanSymbolsRegEx.h"
#include "FileDate.h"

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

FileDate::FileDate() :
    Event(),
    date(),
    language(File::Language::En)
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
        fileDate->parseWday(match[1]);
        fileDate->parseMon(match[2]);
        fileDate->date.tm_mday = std::stoul(match[3]);
        fileDate->date.tm_hour = std::stoul(match[4]);
        fileDate->date.tm_min = std::stoul(match[5]);
        fileDate->date.tm_sec = std::stoul(match[6]);
        if (match[7] == " am")
            fileDate->language = File::Language::En;
        else
        if (match[7] == " pm") {
            fileDate->language = File::Language::En;
            fileDate->date.tm_hour += ((match[7] == " pm") ? 12 : 0);
        } else
            fileDate->language = File::Language::De;
        fileDate->date.tm_year = std::stoul(match[8]) - 1900;
        return fileDate;
    }

    return nullptr;
}

void FileDate::write(File & file, std::ostream & stream)
{
    /* format: "date %s" */
    stream
            << "date "
            << (file.language == File::Language::En ? wdayNameEn[date.tm_wday] : wdayNameDe[date.tm_wday])
            << ' ' << (file.language == File::Language::En ? monNameEn[date.tm_mon] : monNameDe[date.tm_mon])
            << ' ' << std::dec << date.tm_mday
            << ' ' << std::setfill('0') << std::setw(2) << std::dec << (file.language == File::Language::En ? (date.tm_hour % 12) : date.tm_hour)
            << ':' << std::setfill('0') << std::setw(2) << std::dec << date.tm_min
            << ':' << std::setfill('0') << std::setw(2) << std::dec << date.tm_sec
            << (file.language == File::Language::En ? (date.tm_hour < 12 ? " am" : " pm") : "")
            << ' ' << std::dec << date.tm_year + 1900;

    stream << endl;
}

void FileDate::parseWday(std::string wday)
{
    for(int i = 0; i < 7; ++i) {
        if (wdayNameEn[i] == wday) {
            date.tm_wday = i;
            language = File::Language::En;
            return;
        }
    }
    for(int i = 0; i < 7; ++i) {
        if (wdayNameDe[i] == wday) {
            date.tm_wday = i;
            language = File::Language::De;
            return;
        }
    }
    return;
}

void FileDate::parseMon(std::string mon)
{
    for(int i = 0; i < 12; ++i) {
        if (monNameEn[i] == mon) {
            date.tm_mon = i;
            language = File::Language::En;
            return;
        }
    }
    for(int i = 0; i < 12; ++i) {
        if (monNameDe[i] == mon) {
            date.tm_mon = i;
            language = File::Language::De;
            return;
        }
    }
    return;
}

}
}
