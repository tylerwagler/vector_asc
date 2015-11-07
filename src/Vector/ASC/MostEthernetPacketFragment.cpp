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
#include "MostEthernetPacketFragment.h"

namespace Vector {
namespace ASC {

MostEthernetPacketFragment::MostEthernetPacketFragment() :
    Event(),
    time(0.0),
    channel(0),
    frgMask(0),
    sourceMacAdr(0),
    destMacAdr(0),
    ackNack(0),
    pAck(0),
    crc4(0),
    cAck(0),
    rsvdUl(0),
    frgDataLen(0),
    frgDataLenAnnounced(0),
    firstDataLen(0),
    data()
{
    eventType = EventType::MostEthernetPacketFragment;
}

MostEthernetPacketFragment::~MostEthernetPacketFragment()
{
}

MostEthernetPacketFragment * MostEthernetPacketFragment::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " PktEthFrg:"
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
        MostEthernetPacketFragment * mostEthernetPacketFragment = new MostEthernetPacketFragment;
        mostEthernetPacketFragment->time = std::stof(match[1]);
        mostEthernetPacketFragment->channel = std::stoul(match[2]);
        mostEthernetPacketFragment->frgMask = std::stoul(match[3], nullptr, 16);
        mostEthernetPacketFragment->sourceMacAdr = std::stoul(match[4], nullptr, 16);
        mostEthernetPacketFragment->destMacAdr = std::stoul(match[5], nullptr, 16);
        mostEthernetPacketFragment->ackNack = std::stoul(match[6], nullptr, 16);
        mostEthernetPacketFragment->pAck = std::stoul(match[7], nullptr, 16);
        mostEthernetPacketFragment->crc4 = std::stoul(match[8], nullptr, 16);
        mostEthernetPacketFragment->cAck = std::stoul(match[9], nullptr, 16);
        mostEthernetPacketFragment->rsvdUl = std::stoul(match[10], nullptr, 16);
        mostEthernetPacketFragment->frgDataLen = std::stoul(match[11], nullptr, 16);
        mostEthernetPacketFragment->frgDataLenAnnounced = std::stoul(match[12], nullptr, 16);
        mostEthernetPacketFragment->firstDataLen = std::stoul(match[13], nullptr, 16);
        std::istringstream iss(match[14]);
        iss >> std::hex;
        for (uint8_t i = 0; i < mostEthernetPacketFragment->firstDataLen; ++i) {
            unsigned short s;
            iss >> s;
            mostEthernetPacketFragment->data[i] = s;
        }
        return mostEthernetPacketFragment;
    }

    return nullptr;
}

void MostEthernetPacketFragment::write(File & file, std::ostream & stream)
{
}

}
}
