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
#include "EthernetPacket.h"

namespace Vector {
namespace ASC {

EthernetPacket::EthernetPacket() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    dataLen(0),
    data()
{
    eventType = EventType::EthernetPacket;
}

EthernetPacket::~EthernetPacket()
{
}

EthernetPacket * EthernetPacket::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " ETH"
                " ([[:xdigit:]]{1,3})"
                " (Rx|Tx)"
                " ([[:xdigit:]]{1,4}):([[:xdigit:]]*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        EthernetPacket * ethernetPacket = new EthernetPacket;
        ethernetPacket->time = std::stod(match[1]);
        ethernetPacket->channel = std::stoul(match[2], nullptr, file.base);
        if (match[3] == "Rx")
                ethernetPacket->dir = Dir::Rx;
        else
        if (match[3] == "Tx")
                ethernetPacket->dir = Dir::Tx;
        ethernetPacket->dataLen = std::stoul(match[4], nullptr, file.base);
        for (int i = 0; i < ethernetPacket->dataLen; ++i) {
            std::string s;
            s.append(match[5], 2*i, 2);
            ethernetPacket->data[i] = std::stoul(s, nullptr, 16);
        }
        return ethernetPacket;
    }

    return nullptr;
}

void EthernetPacket::write(File & file, std::ostream & stream)
{
#if 0
    stream << getTimeStamp(eventTime);
    stream << ' ' << channel;
    stream << ' ' << (dirTx ? "Tx" : "Rx");
    stream << ' ' << std::hex << dataLen << std::dec;
    stream << ':' << std::hex << std::setfill('0') << std::setw(2);
    for(std::vector<unsigned short>::iterator it=data.begin(); it!=data.end(); ++it) {
        stream << *it;
    }
    stream << std::dec << std::setw(0);
    stream << endl;
#endif
}

}
}
