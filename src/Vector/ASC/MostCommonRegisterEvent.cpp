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
#include "MostCommonRegisterEvent.h"

namespace Vector {
namespace ASC {

MostCommonRegisterEvent::MostCommonRegisterEvent() :
    Event(),
    time(0.0),
    channel(0),
    regSubType(0),
    regChip(0),
    regOffset(0),
    regDataLen(0),
    data()
{
    eventType = EventType::MostCommonRegisterEvent;
}

MostCommonRegisterEvent::~MostCommonRegisterEvent()
{
}

MostCommonRegisterEvent * MostCommonRegisterEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " RegData:"
                " ([[:digit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                "(( [[:xdigit:]]+)*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostCommonRegisterEvent * mostCommonRegisterEvent = new MostCommonRegisterEvent;
        mostCommonRegisterEvent->time = std::stof(match[1]);
        mostCommonRegisterEvent->channel = std::stoul(match[2]);
        mostCommonRegisterEvent->regSubType = std::stoul(match[3]);
        mostCommonRegisterEvent->regChip = std::stoul(match[4], nullptr, 16);
        mostCommonRegisterEvent->regOffset = std::stoul(match[5], nullptr, 16);
        mostCommonRegisterEvent->regDataLen = std::stoul(match[6], nullptr, 16);
        std::istringstream iss(match[7]);
        iss >> std::hex;
        for (uint8_t i = 0; !iss.eof(); ++i) {
            unsigned short s;
            iss >> s;
            mostCommonRegisterEvent->data[i] = s;
        }
        return mostCommonRegisterEvent;
    }

    return nullptr;
}

void MostCommonRegisterEvent::write(File & file, std::ostream & stream)
{
}

}
}
