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
#include "SymbolsRegEx.h"

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
    std::regex regex(REGEX_STOL REGEX_Time  REGEX_WS "CANFD" REGEX_WS REGEX_Channel REGEX_WS REGEX_Dir REGEX_WS REGEX_ID "x"
                     "(" REGEX_WS "([[:alnum:]_]+))?"
                     REGEX_WS REGEX_BRS REGEX_WS REGEX_ESI REGEX_WS REGEX_DLC REGEX_WS REGEX_DataLength
                     "((" REGEX_WS REGEX_Dx "){0,64})"
                     REGEX_WS REGEX_MessageDuration REGEX_WS REGEX_MessageLength
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS REGEX_BitTimingConfArb REGEX_WS REGEX_BitTimingConfData
                     REGEX_ENDL);
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
        if (match[5] != "")
            canFdExtendedMessageEvent->symbolicName = match[6];
        canFdExtendedMessageEvent->brs = (match[7] == '1');
        canFdExtendedMessageEvent->esi = (match[8] == '1');
        canFdExtendedMessageEvent->dlc = std::stoul(match[9], nullptr, 16);
        canFdExtendedMessageEvent->dataLength = std::stoul(match[10]);
        std::istringstream iss(match[11]);
        iss >> std::hex;
        for (uint8_t i = 0; i < canFdExtendedMessageEvent->dataLength && i < 64; ++i) {
            unsigned short s;
            iss >> s;
            canFdExtendedMessageEvent->data[i] = s;
        }
        canFdExtendedMessageEvent->messageDuration = std::stoul(match[13]);
        canFdExtendedMessageEvent->messageLength = std::stoul(match[14]);
        canFdExtendedMessageEvent->flags = std::stoul(match[15]);
        canFdExtendedMessageEvent->crc = std::stoul(match[16], nullptr, 16);
        canFdExtendedMessageEvent->bitTimingConfArb = std::stoul(match[17], nullptr, 16);
        canFdExtendedMessageEvent->bitTimingConfData = std::stoul(match[18], nullptr, 16);
        return canFdExtendedMessageEvent;
    }

    return nullptr;
}

void CanFdExtendedMessageEvent::write(File & file, std::ostream & stream)
{
}

}
}
