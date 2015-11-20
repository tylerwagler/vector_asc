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
#include "Most150AllocTable.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

Most150AllocTable::Most150AllocTable() :
    Event(),
    time(0.0),
    channel(0),
    at150EventModeFlags(0),
    freeBytes(0),
    at150Size(0),
    w()
{
    eventType = EventType::Most150AllocTable;
}

Most150AllocTable::~Most150AllocTable()
{
}

Most150AllocTable * Most150AllocTable::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "AT150:"
                     REGEX_ws REGEX_MOST_AT150EventModeFlags REGEX_WS REGEX_MOST_FreeBytes REGEX_WS REGEX_MOST_AT150Size
                     "((" REGEX_WS REGEX_MOST_Wx ")*)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        Most150AllocTable * most150AllocTable = new Most150AllocTable;
        most150AllocTable->time = std::stod(match[1]);
        most150AllocTable->channel = std::stoul(match[2]);
        most150AllocTable->at150EventModeFlags = std::stoul(match[3], nullptr, 16);
        most150AllocTable->freeBytes = std::stoul(match[4], nullptr, 16);
        most150AllocTable->at150Size = std::stoul(match[5], nullptr, 16);
        std::istringstream iss(match[6]);
        iss >> std::hex;
        for (uint8_t i = 0; i < most150AllocTable->at150Size; ++i) {
            unsigned short s;
            iss >> s;
            most150AllocTable->w[i] = s;
        }
        return most150AllocTable;
    }

    return nullptr;
}

void Most150AllocTable::write(File & file, std::ostream & stream)
{
}

}
}
