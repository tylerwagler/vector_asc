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
#include "CanFdExtendedMessageEvent.h"

namespace Vector {
namespace ASC {

CanFdExtendedMessageEvent::CanFdExtendedMessageEvent() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    id(0),
    symbolicName(),
    brs(false),
    esi(false),
    dlc(0),
    data(),
    messageDuration(0),
    messageLength(0),
    flags(0),
    crc(0),
    bitTimingConfArb(0),
    bitTimingConfData(0)
{
    eventType = EventType::CanFdExtendedMessageEvent;
}

CanFdExtendedMessageEvent::~CanFdExtendedMessageEvent()
{
}

CanFdExtendedMessageEvent * CanFdExtendedMessageEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " CANFD"
                " ([[:digit:]]{1,5})"
                " (Rx|Tx)"
                " ([[:xdigit:]]+)x"
                "( [[:alpha:]_][[:alnum:]_]*)?"
                " ([01])"
                " ([01])"
                " ([[:xdigit:]]+)"
                " ([[:digit:]]+)"
                "(( [[:xdigit:]]+){0,64})"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanFdExtendedMessageEvent * canFdExtendedMessageEvent = new CanFdExtendedMessageEvent;
        canFdExtendedMessageEvent->time = std::stod(match[1]);
        canFdExtendedMessageEvent->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                canFdExtendedMessageEvent->dir = Dir::Rx;
        else
        if (match[3] == "Tx")
                canFdExtendedMessageEvent->dir = Dir::Tx;
        canFdExtendedMessageEvent->id = std::stoul(match[4], nullptr, 16);
        canFdExtendedMessageEvent->symbolicName = match[5];
        canFdExtendedMessageEvent->symbolicName.erase(0, 1);
        canFdExtendedMessageEvent->brs = (match[6] == '1');
        canFdExtendedMessageEvent->esi = (match[7] == '1');
        canFdExtendedMessageEvent->dlc = std::stoul(match[8], nullptr, 16);
        canFdExtendedMessageEvent->dataLength = std::stoul(match[9]);
        std::istringstream iss(match[10]);
        iss >> std::hex;
        for (uint8_t i = 0; i < canFdExtendedMessageEvent->dataLength && i < 64; ++i) {
            unsigned short s;
            iss >> s;
            canFdExtendedMessageEvent->data[i] = s;
        }
        canFdExtendedMessageEvent->messageDuration = std::stoul(match[12]);
        canFdExtendedMessageEvent->messageLength = std::stoul(match[13]);
        canFdExtendedMessageEvent->flags = std::stoul(match[14]);
        canFdExtendedMessageEvent->crc = std::stoul(match[15], nullptr, 16);
        canFdExtendedMessageEvent->bitTimingConfArb = std::stoul(match[16], nullptr, 16);
        canFdExtendedMessageEvent->bitTimingConfData = std::stoul(match[17], nullptr, 16);
        return canFdExtendedMessageEvent;
    }

    return nullptr;
}

void CanFdExtendedMessageEvent::write(File & file, std::ostream & stream)
{
}

}
}
