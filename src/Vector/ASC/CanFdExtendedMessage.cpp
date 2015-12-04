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
#include "CanFdExtendedMessage.h"
#include "CanSymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanFdExtendedMessage::CanFdExtendedMessage() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    id(0),
    symbolicName(),
    brs(false),
    esi(false),
    dlc(0),
    dataLength(0),
    data(),
    messageDuration(0),
    messageLength(0),
    flags(0),
    crc(0),
    bitTimingConfArb(0),
    bitTimingConfData(0)
{
    eventType = EventType::CanFdExtendedMessage;
}

CanFdExtendedMessage::~CanFdExtendedMessage()
{
}

CanFdExtendedMessage * CanFdExtendedMessage::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "CANFD" REGEX_WS REGEX_Channel REGEX_WS REGEX_Dir REGEX_WS REGEX_ID "x"
                     "(" REGEX_WS "([[:alnum:]_]+))?"
                     REGEX_WS REGEX_BRS REGEX_WS REGEX_ESI REGEX_WS REGEX_DLC REGEX_WS REGEX_DataLength
                     "((" REGEX_WS REGEX_Dx "){0,64})"
                     REGEX_WS REGEX_MessageDuration REGEX_WS REGEX_MessageLength
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS REGEX_BitTimingConfArb REGEX_WS REGEX_BitTimingConfData
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanFdExtendedMessage * canFdExtendedMessage = new CanFdExtendedMessage;
        canFdExtendedMessage->time = std::stod(match[1]);
        canFdExtendedMessage->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                canFdExtendedMessage->dir = Dir::Rx;
        else
        if (match[3] == "Tx")
                canFdExtendedMessage->dir = Dir::Tx;
        canFdExtendedMessage->id = std::stoul(match[4], nullptr, 16);
        if (match[5] != "")
            canFdExtendedMessage->symbolicName = match[6];
        canFdExtendedMessage->brs = (match[7] == '1');
        canFdExtendedMessage->esi = (match[8] == '1');
        canFdExtendedMessage->dlc = std::stoul(match[9], nullptr, 16);
        canFdExtendedMessage->dataLength = std::stoul(match[10]);
        std::istringstream iss(match[11]);
        iss >> std::hex;
        while(!iss.eof()) {
            unsigned short s;
            iss >> s;
            canFdExtendedMessage->data.push_back(s);
        }
        canFdExtendedMessage->messageDuration = std::stoul(match[13]);
        canFdExtendedMessage->messageLength = std::stoul(match[14]);
        canFdExtendedMessage->flags = std::stoul(match[15]);
        canFdExtendedMessage->crc = std::stoul(match[16], nullptr, 16);
        canFdExtendedMessage->bitTimingConfArb = std::stoul(match[17], nullptr, 16);
        canFdExtendedMessage->bitTimingConfData = std::stoul(match[18], nullptr, 16);
        return canFdExtendedMessage;
    }

    return nullptr;
}

void CanFdExtendedMessage::write(File & file, std::ostream & stream)
{
    writeTime(file, stream, time);
    stream << ' ' << std::dec << (uint16_t) channel;
    stream << "  ";
    switch(file.base) {
    case 10:
        stream << std::left << std::setfill(' ') << std::setw(15) << std::dec << (uint32_t) id;
        break;
    case 16:
        stream << std::left << std::setfill(' ') << std::setw(15) << std::hex << (uint32_t) id;
        break;
    }
    stream << "x ";
    writeDir(file, stream, dir);
    stream << "   d";
    stream << ' ' << std::hex << (uint16_t) dlc;
    for(Dx d: data) {
        stream << ' ';
        switch(file.base) {
        case 10:
            stream << std::right << std::setfill(' ') << std::setw(3) << std::dec;
            break;
        case 16:
            stream << std::right << std::setfill('0') << std::setw(2) << std::uppercase << std::hex;
            break;
        }
        stream << (uint16_t) d;
    }

    if (file.version >= File::Version::Ver_7_5) {
        stream << ' ';

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

#if 0
    if (file.version >= File::Version::Ver_8_0) {
        /* format: " ID = " */
        stream << " ID = ";

        stream << std::dec << (uint32_t) messageId;
    }
#endif

    stream << endl;
}

}
}
