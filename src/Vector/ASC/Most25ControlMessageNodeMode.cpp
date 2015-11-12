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
#include "Most25ControlMessageNodeMode.h"

namespace Vector {
namespace ASC {

Most25ControlMessageNodeMode::Most25ControlMessageNodeMode() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    sourceAdr(0),
    destAdr(0),
    rType(0),
    data(),
    state2(0)
{
    eventType = EventType::Most25ControlMessageNodeMode;
}

Most25ControlMessageNodeMode::~Most25ControlMessageNodeMode()
{
}

Most25ControlMessageNodeMode * Most25ControlMessageNodeMode::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " (Rx|Tx)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                "(( [[:xdigit:]]+){17})"
                " ([[:xdigit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        Most25ControlMessageNodeMode * most25ControlMessageNodeMode = new Most25ControlMessageNodeMode;
        most25ControlMessageNodeMode->time = std::stod(match[1]);
        most25ControlMessageNodeMode->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                most25ControlMessageNodeMode->dir = Dir::Rx;
        else
        if (match[3] == "Tx")
                most25ControlMessageNodeMode->dir = Dir::Tx;
        most25ControlMessageNodeMode->sourceAdr = std::stoul(match[4], nullptr, 16);
        most25ControlMessageNodeMode->destAdr = std::stoul(match[5], nullptr, 16);
        most25ControlMessageNodeMode->rType = std::stoul(match[6], nullptr, 16);
        std::istringstream iss(match[7]);
        iss >> std::hex;
        uint8_t i = 0;
        for (i = 0; !iss.eof(); ++i) {
            unsigned short s;
            iss >> s;
            most25ControlMessageNodeMode->data[i] = s;
        }
        most25ControlMessageNodeMode->state2 = std::stoul(match[9], nullptr, 16);
        return most25ControlMessageNodeMode;
    }

    return nullptr;
}

void Most25ControlMessageNodeMode::write(File & file, std::ostream & stream)
{
}

}
}
