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
#include "Most25AllocTable.h"

namespace Vector {
namespace ASC {

Most25AllocTable::Most25AllocTable() :
    Event(),
    time(0.0),
    channel(0),
    allocTableSize(0),
    data()
{
    eventType = EventType::Most25AllocTable;
}

Most25AllocTable::~Most25AllocTable()
{
}

Most25AllocTable * Most25AllocTable::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " AllocTab:"
                " ([[:xdigit:]]+)"
                "(( [[:xdigit:]]+)*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        Most25AllocTable * most25AllocTable = new Most25AllocTable;
        most25AllocTable->time = std::stof(match[1]);
        most25AllocTable->channel = std::stoul(match[2]);
        most25AllocTable->allocTableSize = std::stoul(match[3], nullptr, 16);
        std::istringstream iss(match[4]);
        iss >> std::hex;
        for (uint8_t i = 0; i < most25AllocTable->allocTableSize; ++i) {
            unsigned short s;
            iss >> s;
            most25AllocTable->data[i] = s;
        }
        return most25AllocTable;
    }

    return nullptr;
}

void Most25AllocTable::write(File & file, std::ostream & stream)
{
}

}
}
