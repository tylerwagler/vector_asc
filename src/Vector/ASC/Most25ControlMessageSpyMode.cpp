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
#include "Most25ControlMessageSpyMode.h"

namespace Vector {
namespace ASC {

Most25ControlMessageSpyMode::Most25ControlMessageSpyMode() :
    Event(),
    time(0.0),
    channel(0),
    sourceAdr(0),
    destAdr(0),
    rType(0),
    data(),
    state(0),
    ackNack(0),
    crc(0)
{
    eventType = EventType::Most25ControlMessageSpyMode;
}

Most25ControlMessageSpyMode::~Most25ControlMessageSpyMode()
{
}

Most25ControlMessageSpyMode * Most25ControlMessageSpyMode::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " Rx"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                "(( [[:xdigit:]]+){17})"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        Most25ControlMessageSpyMode * most25ControlMessageSpyMode = new Most25ControlMessageSpyMode;
        most25ControlMessageSpyMode->time = std::stof(match[1]);
        most25ControlMessageSpyMode->channel = std::stoul(match[2]);
        most25ControlMessageSpyMode->sourceAdr = std::stoul(match[3], nullptr, 16);
        most25ControlMessageSpyMode->destAdr = std::stoul(match[4], nullptr, 16);
        most25ControlMessageSpyMode->rType = std::stoul(match[5], nullptr, 16);
        std::istringstream iss(match[6]);
        iss >> std::hex;
        for (uint8_t i = 0; !iss.eof(); ++i) {
            unsigned short s;
            iss >> s;
            most25ControlMessageSpyMode->data[i] = s;
        }
        most25ControlMessageSpyMode->state = std::stoul(match[8], nullptr, 16);
        most25ControlMessageSpyMode->ackNack = std::stoul(match[9], nullptr, 16);
        most25ControlMessageSpyMode->crc = std::stoul(match[10], nullptr, 16);
        return most25ControlMessageSpyMode;
    }

    return nullptr;
}

void Most25ControlMessageSpyMode::write(File & file, std::ostream & stream)
{
}

}
}
