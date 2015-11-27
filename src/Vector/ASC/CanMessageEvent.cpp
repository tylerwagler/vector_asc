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
#include "CanMessageEvent.h"
#include "CanSymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanMessageEvent::CanMessageEvent() :
    Event(),
    time(0.0),
    channel(0),
    id(0),
    dir(Dir::Rx),
    dlc(0),
    data(),
    messageDuration(0),
    messageLength(0),
    messageId(),
    messageFlags()
{
    eventType = EventType::CanMessageEvent;
}

CanMessageEvent::~CanMessageEvent()
{
}

CanMessageEvent * CanMessageEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS REGEX_Channel REGEX_WS REGEX_ID REGEX_WS REGEX_Dir REGEX_WS "d" REGEX_WS REGEX_DLC
                     "((" REGEX_WS REGEX_Dx "){0,8})"
                     "(" REGEX_WS "Length" REGEX_ws "=" REGEX_ws REGEX_MessageDuration ")?"
                     "(" REGEX_WS "BitCount" REGEX_ws "=" REGEX_ws REGEX_MessageLength ")?"
                     "(" REGEX_WS REGEX_MessageFlags ")?"
                     "(" REGEX_WS "ID" REGEX_ws "=" REGEX_ws REGEX_IDnum ")?"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanMessageEvent * canMessageEvent = new CanMessageEvent;
        canMessageEvent->time = std::stod(match[1]);
        canMessageEvent->channel = std::stoul(match[2]);
        canMessageEvent->id = std::stoul(match[3], nullptr, file.base);
        if (match[4] == "Rx")
                canMessageEvent->dir = Dir::Rx;
        else
        if (match[4] == "Tx")
                canMessageEvent->dir = Dir::Tx;
        canMessageEvent->dlc = std::stoul(match[5], nullptr, file.base);
        std::istringstream iss(match[6]);
        if (file.base == 10)
            iss >> std::dec;
        if (file.base == 16)
            iss >> std::hex;
        for (uint8_t i = 0; i < canMessageEvent->dlc && i < 8; ++i) {
            unsigned short s;
            iss >> s;
            canMessageEvent->data[i] = s;
        }
        if (match[8] != "")
            canMessageEvent->messageDuration = std::stoul(match[9]);
        if (match[10] != "")
            canMessageEvent->messageLength = std::stoul(match[11]);
        if (match[12] != "") {
            if (match[13] == "TE")
                canMessageEvent->messageFlags.te = true;
            else
            if (match[13] == "WU")
                canMessageEvent->messageFlags.wu = true;
            else
            if (match[13] == "XX") {
                canMessageEvent->messageFlags.te = true;
                canMessageEvent->messageFlags.wu = true;
            }
        }
        if (match[14] != "")
            canMessageEvent->messageId = std::stoul(match[15]);
        return canMessageEvent;
    }

    return nullptr;
}

void CanMessageEvent::write(File & file, std::ostream & stream)
{
    writeTime(file, stream, time);
    stream << ' ' << std::dec << (uint16_t) channel;
    stream << ' ';
    // stream << std::setfill(' ') << std::setw(4) << std::hex << (uint32_t) id;
    stream << std::setfill(' ') << std::setw(4) << std::dec << (uint32_t) id;
    stream << "             ";
    writeDir(file, stream, dir);
    stream << "   d";
    stream << ' ' << std::hex << (uint16_t) dlc;
    for(int i = 0; i < dlc && i < 8; ++i) {
        stream << ' ';
        // stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex;
        stream << std::setfill(' ') << std::setw(3) << std::dec;
        stream << (uint16_t) data[i];
    }
    stream << ' ';

    if (file.version >= File::Version::Ver_7_5) {
        /* format: " Length= " */
        stream << " Length = ";

        stream << std::dec << (uint32_t) messageDuration;

        /* format: " BitCount = " */
        stream << " BitCount = ";

        stream << std::dec << (uint32_t) messageLength;
    }

#if 0
    /* <MessageFlags> */
    if (!messageFlags.empty()) {
        stream << ' ' << std::dec << (uint32_t) messageFlags;
    }
#endif

    if (file.version >= File::Version::Ver_8_0) {
        /* format: " ID = " */
        stream << " ID = ";

        stream << std::dec << (uint32_t) messageId;
    }

    stream << endl;
}

}
}
