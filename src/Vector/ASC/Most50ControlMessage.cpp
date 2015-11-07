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
#include "Most50ControlMessage.h"

namespace Vector {
namespace ASC {

Most50ControlMessage::Most50ControlMessage() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    sourceAdr(0),
    destAdr(0),
    state(0),
    ackNack(0),
    transferType(0),
    rsvdUc1(0),
    priority(0),
    rsvdUc2(0),
    crc2(0),
    rsvdUc3(0),
    rsvdUl(0),
    msg50Len(0),
    data()
{
    eventType = EventType::Most50ControlMessage;
}

Most50ControlMessage::~Most50ControlMessage()
{
}

Most50ControlMessage * Most50ControlMessage::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " Msg50:"
                " (Rx|Tx)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                "(( [[:xdigit:]]+)*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        Most50ControlMessage * most50ControlMessage = new Most50ControlMessage;
        most50ControlMessage->time = std::stof(match[1]);
        most50ControlMessage->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                most50ControlMessage->dir = Dir::Rx;
        if (match[3] == "Tx")
                most50ControlMessage->dir = Dir::Tx;
        most50ControlMessage->sourceAdr = std::stoul(match[4], nullptr, 16);
        most50ControlMessage->destAdr = std::stoul(match[5], nullptr, 16);
        most50ControlMessage->state = std::stoul(match[6], nullptr, 16);
        most50ControlMessage->ackNack = std::stoul(match[7], nullptr, 16);
        most50ControlMessage->transferType = std::stoul(match[8], nullptr, 16);
        most50ControlMessage->rsvdUc1 = std::stoul(match[9], nullptr, 16);
        most50ControlMessage->priority = std::stoul(match[10], nullptr, 16);
        most50ControlMessage->rsvdUc2 = std::stoul(match[11], nullptr, 16);
        most50ControlMessage->crc2 = std::stoul(match[12], nullptr, 16);
        most50ControlMessage->rsvdUc3 = std::stoul(match[13], nullptr, 16);
        most50ControlMessage->rsvdUl = std::stoul(match[14], nullptr, 16);
        most50ControlMessage->msg50Len = std::stoul(match[15], nullptr, 16);
        std::istringstream iss(match[16]);
        iss >> std::hex;
        for (uint8_t i = 0; i < most50ControlMessage->msg50Len; ++i) {
            unsigned short s;
            iss >> s;
            most50ControlMessage->data[i] = s;
        }
        return most50ControlMessage;
    }

    return nullptr;
}

void Most50ControlMessage::write(File & file, std::ostream & stream)
{
}

}
}
