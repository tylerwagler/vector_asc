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
#include "CanCommon.h"
#include "CanExtendedMessageEvent.h"
#include "CanSymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanExtendedMessageEvent::CanExtendedMessageEvent() :
    Event(),
    time(0.0),
    channel(0),
    id(0),
    dir(Dir::Rx),
    dlc(0),
    data(),
    messageDuration(0),
    messageLength(0),
    messageFlags()
{
    eventType = EventType::CanExtendedMessageEvent;
}

CanExtendedMessageEvent::~CanExtendedMessageEvent()
{
}

CanExtendedMessageEvent * CanExtendedMessageEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS REGEX_Channel REGEX_WS REGEX_ID "x" REGEX_WS REGEX_Dir REGEX_WS "d" REGEX_WS REGEX_DLC
                     "((" REGEX_WS REGEX_Dx "){0,8})"
                     "(" REGEX_WS "Length" REGEX_ws "=" REGEX_ws REGEX_MessageDuration ")?"
                     "(" REGEX_WS "BitCount" REGEX_ws "=" REGEX_ws REGEX_MessageLength ")?"
                     "(" REGEX_WS REGEX_MessageFlags ")?"
                     "(" REGEX_WS "ID" REGEX_ws "=" REGEX_ws REGEX_IDnum "x)?"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanExtendedMessageEvent * canExtendedMessageEvent = new CanExtendedMessageEvent;
        canExtendedMessageEvent->time = std::stod(match[1]);
        canExtendedMessageEvent->channel = std::stoul(match[2]);
        canExtendedMessageEvent->id = std::stoul(match[3], nullptr, file.base);
        if (match[4] == "Rx")
                canExtendedMessageEvent->dir = Dir::Rx;
        else
        if (match[4] == "Tx")
                canExtendedMessageEvent->dir = Dir::Tx;
        canExtendedMessageEvent->dlc = std::stoul(match[5], nullptr, file.base);
        std::istringstream iss(match[6]);
        if (file.base == 10)
            iss >> std::dec;
        if (file.base == 16)
            iss >> std::hex;
        for (uint8_t i = 0; i < canExtendedMessageEvent->dlc && i < 8; ++i) {
            unsigned short s;
            iss >> s;
            canExtendedMessageEvent->data[i] = s;
        }
        if (match[8] != "")
            canExtendedMessageEvent->messageDuration = std::stoul(match[9]);
        if (match[10] != "")
            canExtendedMessageEvent->messageLength = std::stoul(match[11]);
        if (match[12] != "") {
            if (match[13] == " TE")
                canExtendedMessageEvent->messageFlags.te = true;
            else
            if (match[13] == " WU")
                canExtendedMessageEvent->messageFlags.wu = true;
            else
            if (match[13] == " XX") {
                canExtendedMessageEvent->messageFlags.te = true;
                canExtendedMessageEvent->messageFlags.wu = true;
            }
        }
        if (match[14] != "")
            canExtendedMessageEvent->messageId = std::stoul(match[15], nullptr, 16);
        return canExtendedMessageEvent;
    }

    return nullptr;
}

void CanExtendedMessageEvent::write(File & file, std::ostream & stream)
{
    writeTime(file, stream, time);

    stream << endl;
}

}
}
