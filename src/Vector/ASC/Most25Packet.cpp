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
#include "Most25Packet.h"

namespace Vector {
namespace ASC {

Most25Packet::Most25Packet() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    sourceAdr(0),
    destAdr(0),
    pktState(0),
    transferType(0),
    pktPrio(0),
    pktArbitr(0),
    crc2(0),
    pktLen(0),
    data()
{
    eventType = EventType::Most25Packet;
}

Most25Packet::~Most25Packet()
{
}

Most25Packet * Most25Packet::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " Pkt:"
                " (Rx|Tx)"
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
        Most25Packet * most25Packet = new Most25Packet;
        most25Packet->time = std::stof(match[1]);
        most25Packet->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                most25Packet->dir = Dir::Rx;
        if (match[3] == "Tx")
                most25Packet->dir = Dir::Tx;
        most25Packet->sourceAdr = std::stoul(match[4], nullptr, 16);
        most25Packet->destAdr = std::stoul(match[5], nullptr, 16);
        most25Packet->pktState = std::stoul(match[6], nullptr, 16);
        most25Packet->transferType = std::stoul(match[7], nullptr, 16);
        most25Packet->pktPrio = std::stoul(match[8], nullptr, 16);
        most25Packet->pktArbitr = std::stoul(match[9], nullptr, 16);
        most25Packet->crc2 = std::stoul(match[10], nullptr, 16);
        most25Packet->pktLen = std::stoul(match[11], nullptr, 16);
        std::istringstream iss(match[12]);
        iss >> std::hex;
        for (uint8_t i = 0; i < most25Packet->pktLen; ++i) {
            unsigned short s;
            iss >> s;
            most25Packet->data[i] = s;
        }
        return most25Packet;
    }

    return nullptr;
}

void Most25Packet::write(File & file, std::ostream & stream)
{
}

}
}
