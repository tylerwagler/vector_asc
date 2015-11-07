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
#include "Most150Packet.h"

namespace Vector {
namespace ASC {

Most150Packet::Most150Packet() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    sourceAdr(0),
    destAdr(0),
    state(0),
    ackNack(0),
    transferType(0),
    pAck(0),
    rsvdUc(0),
    pIndex(0),
    crc2(0),
    cAck(0),
    rsvdUl(0),
    pkt150Len(0),
    data()
{
    eventType = EventType::Most150Packet;
}

Most150Packet::~Most150Packet()
{
}

Most150Packet * Most150Packet::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " Pkt150:"
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
        Most150Packet * most150Packet = new Most150Packet;
        most150Packet->time = std::stof(match[1]);
        most150Packet->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                most150Packet->dir = Dir::Rx;
        if (match[3] == "Tx")
                most150Packet->dir = Dir::Tx;
        most150Packet->sourceAdr = std::stoul(match[4], nullptr, 16);
        most150Packet->destAdr = std::stoul(match[5], nullptr, 16);
        most150Packet->state = std::stoul(match[6], nullptr, 16);
        most150Packet->ackNack = std::stoul(match[7], nullptr, 16);
        most150Packet->transferType = std::stoul(match[8], nullptr, 16);
        most150Packet->pAck = std::stoul(match[9], nullptr, 16);
        most150Packet->rsvdUc = std::stoul(match[10], nullptr, 16);
        most150Packet->pIndex = std::stoul(match[11], nullptr, 16);
        most150Packet->crc2 = std::stoul(match[12], nullptr, 16);
        most150Packet->cAck = std::stoul(match[13], nullptr, 16);
        most150Packet->rsvdUl = std::stoul(match[14], nullptr, 16);
        most150Packet->pkt150Len = std::stoul(match[15], nullptr, 16);
        std::istringstream iss(match[16]);
        iss >> std::hex;
        for (uint8_t i = 0; i < most150Packet->pkt150Len; ++i) {
            unsigned short s;
            iss >> s;
            most150Packet->data[i] = s;
        }
        return most150Packet;
    }

    return nullptr;
}

void Most150Packet::write(File & file, std::ostream & stream)
{
}

}
}
