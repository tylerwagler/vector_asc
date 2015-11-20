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
#include "CanFdMessageEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanFdMessageEvent::CanFdMessageEvent() :
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
    eventType = EventType::CanFdMessageEvent;
}

CanFdMessageEvent::~CanFdMessageEvent()
{
}

CanFdMessageEvent * CanFdMessageEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time  REGEX_WS "CANFD" REGEX_WS REGEX_Channel REGEX_WS REGEX_Dir REGEX_WS REGEX_ID
                     "(" REGEX_WS "([[:alnum:]_]+))?"
                     REGEX_WS REGEX_BRS REGEX_WS REGEX_ESI REGEX_WS REGEX_DLC REGEX_WS REGEX_DataLength
                     "((" REGEX_WS REGEX_Dx "){0,64})"
                     REGEX_WS REGEX_MessageDuration REGEX_WS REGEX_MessageLength
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS REGEX_BitTimingConfArb REGEX_WS REGEX_BitTimingConfData
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanFdMessageEvent * canFdMessageEvent = new CanFdMessageEvent;
        canFdMessageEvent->time = std::stod(match[1]);
        canFdMessageEvent->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                canFdMessageEvent->dir = Dir::Rx;
        else
        if (match[3] == "Tx")
                canFdMessageEvent->dir = Dir::Tx;
        canFdMessageEvent->id = std::stoul(match[4], nullptr, 16);
        if (match[5] != "")
            canFdMessageEvent->symbolicName = match[6];
        canFdMessageEvent->brs = (match[7] == '1');
        canFdMessageEvent->esi = (match[8] == '1');
        canFdMessageEvent->dlc = std::stoul(match[9], nullptr, file.base);
        canFdMessageEvent->dataLength = std::stoul(match[10]);
        std::istringstream iss(match[11]);
        iss >> std::hex;
        for (uint8_t i = 0; i < canFdMessageEvent->dataLength && i < 64; ++i) {
            unsigned short s;
            iss >> s;
            canFdMessageEvent->data[i] = s;
        }
        canFdMessageEvent->messageDuration = std::stoul(match[13]);
        canFdMessageEvent->messageLength = std::stoul(match[14]);
        canFdMessageEvent->flags = std::stoul(match[15]);
        canFdMessageEvent->crc = std::stoul(match[16], nullptr, 16);
        canFdMessageEvent->bitTimingConfArb = std::stoul(match[17], nullptr, 16);
        canFdMessageEvent->bitTimingConfData = std::stoul(match[18], nullptr, 16);
        return canFdMessageEvent;
    }

    return nullptr;
}

void CanFdMessageEvent::write(File & file, std::ostream & stream)
{
}

}
}
