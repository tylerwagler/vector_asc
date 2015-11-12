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
#include "CanMessageEvent.h"

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
    std::regex regex(
                "^([[:digit:].]+)"
                " ([[:digit:]]{1,5})"
                " ([[:xdigit:]]+)"
                " (Rx|Tx)"
                " d"
                " ([[:xdigit:]]{1,2})"
                "(( [[:xdigit:]]{1,3}){0,8})"
                "( Length = ([[:digit:]]+))?"
                "( BitCount = ([[:digit:]]+))?"
                "( (TE|WU|XX))?"
                "( ID = ([[:xdigit:]]+))?$");
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
        canMessageEvent->messageDuration = std::stoul(match[9]);
        canMessageEvent->messageLength = std::stoul(match[11]);
        if (match[13] == " TE")
            canMessageEvent->messageFlags.te = true;
        else
        if (match[13] == " WU")
            canMessageEvent->messageFlags.wu = true;
        else
        if (match[13] == " XX") {
            canMessageEvent->messageFlags.te = true;
            canMessageEvent->messageFlags.wu = true;
        }
        canMessageEvent->messageId = std::stoul(match[15], nullptr, 16);
        return canMessageEvent;
    }

    return nullptr;
}

void CanMessageEvent::write(File & file, std::ostream & stream)
{
#if 0
    /* <Time> */
    stream << std::setw(11) << std::setfill(' ');
    stream << std::fixed << time;

    /* <Channel> */
    stream ' ' << channel;

    /* <ID> */
    stream << ' ';
    stream << std::setw(4) << std::setfill(' ') << std::hex << id;
    stream << (extended ? 'x' : ' ');

    /* space */
    stream << "           ";

    /* <Dir> */
    stream << ' ' << (dirTx ? "Tx" : "Rx");

    /* space */
    stream << "  ";

    /* d */
    stream << ' ' << "d";

    /* <DLC> */
    stream << ' ' << std::hex << dlc;

    /* <D0> <D1>...<D8> */
    for(std::vector<unsigned short>::iterator it=data.begin(); it!=data.end(); ++it) {
        stream << ' ';
        stream << std::setw(2) << std::setfill('0') << std::setiosflags(std::ifstream::uppercase | std::ifstream::right);
        stream << *it;
    }
    stream << std::dec << std::setw(0);

    /* Length = <MessageDuration> BitCount = <MessageLength> */
    if (version >= Version::Ver_7_5) {
        stream << " Length = " << length;
        stream << " BitCount = " << bitCount;
    }

    /* <MessageFlags> */
    if (!messageFlags.empty()) {
        stream << ' ' << messageFlags;
    }

    stream << endl;
#endif
}

}
}
