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
#include "MostEthernetPacket.h"

namespace Vector {
namespace ASC {

MostEthernetPacket::MostEthernetPacket() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    sourceMacAdr(0),
    destMacAdr(0),
    state(0),
    ackNack(0),
    transferType(0),
    pAck(0),
    crc4(0),
    cAck(0),
    rsvdUl(0),
    pktEthLen(0),
    data()
{
    eventType = EventType::MostEthernetPacket;
}

MostEthernetPacket::~MostEthernetPacket()
{
}

MostEthernetPacket * MostEthernetPacket::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " PktEth:"
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
                "(( [[:xdigit:]]+)*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostEthernetPacket * mostEthernetPacket = new MostEthernetPacket;
        mostEthernetPacket->time = std::stof(match[1]);
        mostEthernetPacket->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                mostEthernetPacket->dir = Dir::Rx;
        if (match[3] == "Tx")
                mostEthernetPacket->dir = Dir::Tx;
        mostEthernetPacket->sourceMacAdr = std::stoul(match[4], nullptr, 16);
        mostEthernetPacket->destMacAdr = std::stoul(match[5], nullptr, 16);
        mostEthernetPacket->state = std::stoul(match[6], nullptr, 16);
        mostEthernetPacket->ackNack = std::stoul(match[7], nullptr, 16);
        mostEthernetPacket->transferType = std::stoul(match[8], nullptr, 16);
        mostEthernetPacket->pAck = std::stoul(match[9], nullptr, 16);
        mostEthernetPacket->crc4 = std::stoul(match[10], nullptr, 16);
        mostEthernetPacket->cAck = std::stoul(match[11], nullptr, 16);
        mostEthernetPacket->rsvdUl = std::stoul(match[12], nullptr, 16);
        mostEthernetPacket->pktEthLen = std::stoul(match[13], nullptr, 16);
        std::istringstream iss(match[14]);
        iss >> std::hex;
        for (uint8_t i = 0; i < mostEthernetPacket->pktEthLen; ++i) {
            unsigned short s;
            iss >> s;
            mostEthernetPacket->data[i] = s;
        }
        return mostEthernetPacket;
    }

    return nullptr;
}

void MostEthernetPacket::write(File & file, std::ostream & stream)
{
}

}
}
