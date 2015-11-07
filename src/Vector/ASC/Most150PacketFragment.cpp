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
#include "Most150PacketFragment.h"

namespace Vector {
namespace ASC {

Most150PacketFragment::Most150PacketFragment() :
    Event(),
    time(0.0),
    channel(0),
    frgMask(0),
    sourceAdr(0),
    destAdr(0),
    ackNack(0),
    pAck(0),
    rsvdUc(0),
    pIndex(0),
    crc2(0),
    cAck(0),
    rsvdUl(0),
    frgDataLen(0),
    frgDataLenAnnounced(0),
    firstDataLen(0),
    data()
{
    eventType = EventType::Most150PacketFragment;
}

Most150PacketFragment::~Most150PacketFragment()
{
}

Most150PacketFragment * Most150PacketFragment::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " Pkt150Frg:"
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
                " ([[:xdigit:]]+)"
                "(( [[:xdigit:]]+)*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        Most150PacketFragment * most150PacketFragment = new Most150PacketFragment;
        most150PacketFragment->time = std::stof(match[1]);
        most150PacketFragment->channel = std::stoul(match[2]);
        most150PacketFragment->frgMask = std::stoul(match[3], nullptr, 16);
        most150PacketFragment->sourceAdr = std::stoul(match[4], nullptr, 16);
        most150PacketFragment->destAdr = std::stoul(match[5], nullptr, 16);
        most150PacketFragment->ackNack = std::stoul(match[6], nullptr, 16);
        most150PacketFragment->pAck = std::stoul(match[7], nullptr, 16);
        most150PacketFragment->rsvdUc = std::stoul(match[8], nullptr, 16);
        most150PacketFragment->pIndex = std::stoul(match[9], nullptr, 16);
        most150PacketFragment->crc2 = std::stoul(match[10], nullptr, 16);
        most150PacketFragment->cAck = std::stoul(match[11], nullptr, 16);
        most150PacketFragment->rsvdUl = std::stoul(match[12], nullptr, 16);
        most150PacketFragment->frgDataLen = std::stoul(match[13], nullptr, 16);
        most150PacketFragment->frgDataLenAnnounced = std::stoul(match[14], nullptr, 16);
        most150PacketFragment->firstDataLen = std::stoul(match[15], nullptr, 16);
        std::istringstream iss(match[16]);
        iss >> std::hex;
        for (uint8_t i = 0; i < most150PacketFragment->firstDataLen; ++i) {
            unsigned short s;
            iss >> s;
            most150PacketFragment->data[i] = s;
        }
        return most150PacketFragment;
    }

    return nullptr;
}

void Most150PacketFragment::write(File & file, std::ostream & stream)
{
}

}
}
