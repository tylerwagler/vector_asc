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
#include "FlexRayOldStartCycleEvent.h"

namespace Vector {
namespace ASC {

FlexRayOldStartCycleEvent::FlexRayOldStartCycleEvent() :
    Event(),
    time(0.0),
    channel(),
    dlc(0),
    data()
{
    eventType = EventType::FlexRayOldStartCycleEvent;
}

FlexRayOldStartCycleEvent::~FlexRayOldStartCycleEvent()
{
}

FlexRayOldStartCycleEvent * FlexRayOldStartCycleEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " Fr"
                " ([12*])"
                " StartCycleEvent"
                " NM Vector:"
                " ([[:digit:]]+)"
                "(( [[:xdigit:]]+){0,255})$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayOldStartCycleEvent * flexRayOldStartCycleEvent = new FlexRayOldStartCycleEvent;
        flexRayOldStartCycleEvent->time = std::stod(match[1]);
        flexRayOldStartCycleEvent->channel = std::string(match[2])[0];
        flexRayOldStartCycleEvent->dlc = std::stoul(match[3]);
        std::istringstream iss(match[4]);
        for (uint8_t i = 0; i < flexRayOldStartCycleEvent->dlc && i <= 255; ++i) {
            unsigned short s;
            iss >> s;
            flexRayOldStartCycleEvent->data[i] = s;
        }
        return flexRayOldStartCycleEvent;
    }

    return nullptr;
}

void FlexRayOldStartCycleEvent::write(File & file, std::ostream & stream)
{
}

}
}
