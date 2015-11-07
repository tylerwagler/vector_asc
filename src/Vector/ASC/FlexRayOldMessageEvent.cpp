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
#include "FlexRayOldMessageEvent.h"

namespace Vector {
namespace ASC {

FlexRayOldMessageEvent::FlexRayOldMessageEvent() :
    Event(),
    time(0.0),
    channel(),
    typ(),
    id(0),
    cycle(0),
    nm(false),
    sync(false),
    headerCrc(0),
    symbolicName(),
    dlc(0),
    data(),
    frameState(0),
    headerBitMask(0)
{
    eventType = EventType::FlexRayOldMessageEvent;
}

FlexRayOldMessageEvent::~FlexRayOldMessageEvent()
{
}

FlexRayOldMessageEvent * FlexRayOldMessageEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " Fr"
                " ([12*])"
                " (V9)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([01])"
                " ([01])"
                " ([[:digit:]]+)"
                " ([[:alnum:]_]+)"
                " ([[:digit:]]+)"
                "(( [[:xdigit:]]+){0,255})"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayOldMessageEvent * flexRayOldMessageEvent = new FlexRayOldMessageEvent;
        flexRayOldMessageEvent->time = std::stof(match[1]);
        flexRayOldMessageEvent->channel = match[2];
        flexRayOldMessageEvent->typ = match[3];
        flexRayOldMessageEvent->id = std::stoul(match[4]);
        flexRayOldMessageEvent->cycle = std::stoul(match[5]);
        flexRayOldMessageEvent->nm = (match[6] == '1');
        flexRayOldMessageEvent->sync = (match[7] == '1');
        flexRayOldMessageEvent->headerCrc = std::stoul(match[8]);
        flexRayOldMessageEvent->symbolicName = match[9];
        flexRayOldMessageEvent->dlc = std::stoul(match[10]);
        std::istringstream iss(match[11]);
        for (uint8_t i = 0; i < flexRayOldMessageEvent->dlc && i <= 255; ++i) {
            unsigned short s;
            iss >> s;
            flexRayOldMessageEvent->data[i] = s;
        }
        flexRayOldMessageEvent->frameState = std::stoul(match[13], nullptr, 16);
        flexRayOldMessageEvent->headerBitMask = std::stoul(match[14], nullptr, 16);
        return flexRayOldMessageEvent;
    }

    return nullptr;
}

void FlexRayOldMessageEvent::write(File & file, std::ostream & stream)
{
}

}
}
