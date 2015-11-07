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
#include "KLineMessageEvent.h"

namespace Vector {
namespace ASC {

KLineMessageEvent::KLineMessageEvent() :
    Event(),
    time(0.0),
    port(),
    direction(Dir::Rx),
    baudrate(0),
    source(0),
    destination(0),
    length(0),
    data()
{
    eventType = EventType::KLineMessageEvent;
}

KLineMessageEvent::~KLineMessageEvent()
{
}

KLineMessageEvent * KLineMessageEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^// K-Line:"
                " ([[:digit:].]+)"
                " (COM[[:digit:]]+)"
                " (Rx|Tx)"
                " ([[:digit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:digit:]]+)"
                "(( [[:xdigit:]]+)*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        KLineMessageEvent * kLineMessageEvent = new KLineMessageEvent;
        kLineMessageEvent->time = std::stof(match[1]);
        kLineMessageEvent->port = match[2];
        if (match[3] == "Rx")
                kLineMessageEvent->direction = Dir::Rx;
        if (match[3] == "Tx")
                kLineMessageEvent->direction = Dir::Tx;
        kLineMessageEvent->baudrate = std::stoul(match[4]);
        kLineMessageEvent->source = std::stoul(match[5], nullptr, 16);
        kLineMessageEvent->destination = std::stoul(match[6], nullptr, 16);
        kLineMessageEvent->length = std::stoul(match[7]);
        std::istringstream iss(match[8]);
        iss >> std::hex;
        for (uint8_t i = 0; i < kLineMessageEvent->length; ++i) {
            unsigned short s;
            iss >> s;
            kLineMessageEvent->data[i] = s;
        }
        return kLineMessageEvent;
    }

    return nullptr;
}

void KLineMessageEvent::write(File & file, std::ostream & stream)
{
}

}
}
