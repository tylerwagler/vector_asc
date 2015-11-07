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
#include "AfdxPacket.h"

namespace Vector {
namespace ASC {

AfdxPacket::AfdxPacket() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    ethChannel(0),
    flags(0),
    bag(0),
    dataLen(0),
    data()
{
    eventType = EventType::AfdxPacket;
}

AfdxPacket * AfdxPacket::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " AFDX"
                " ([[:digit:]]+)"
                " (Rx|Tx)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:xdigit:]]+):([[:xdigit:]]*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        AfdxPacket * afdxPacket = new AfdxPacket;
        afdxPacket->time = std::stof(match[1]);
        afdxPacket->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                afdxPacket->dir = Dir::Rx;
        if (match[3] == "Tx")
                afdxPacket->dir = Dir::Tx;
        afdxPacket->ethChannel = std::stoul(match[4], nullptr, 16);
        afdxPacket->flags = std::stoul(match[5]);
        afdxPacket->bag = std::stoul(match[6], nullptr, 16);
        afdxPacket->dataLen = std::stoul(match[7], nullptr, 16);
        for (int i = 0; i < afdxPacket->dataLen; ++i) {
            std::string s;
            s.append(match[8], 2*i, 2);
            afdxPacket->data[i] = std::stoul(s, nullptr, 16);
        }
        return afdxPacket;
    }

    return nullptr;
}

void AfdxPacket::write(File & file, std::ostream & stream)
{
}

}
}
