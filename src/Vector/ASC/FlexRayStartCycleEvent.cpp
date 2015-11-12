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
#include "FlexRayStartCycleEvent.h"

namespace Vector {
namespace ASC {

FlexRayStartCycleEvent::FlexRayStartCycleEvent() :
    Event(),
    time(0.0),
    clusterNr(0),
    clientId(0),
    channelNr(0),
    channelMask(0),
    cycleNo(0),
    direction(),
    ccType(0),
    ccData(),
    nmVectL(0),
    nmVect()
{
    eventType = EventType::FlexRayStartCycleEvent;
}

FlexRayStartCycleEvent::~FlexRayStartCycleEvent()
{
}

FlexRayStartCycleEvent * FlexRayStartCycleEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " Fr"
                " SCE"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:xdigit:]]+)"
                " (Rx|Tx)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " NM_Vector:"
                " ([[:xdigit:]]+)"
                "(( [[:xdigit:]]+)*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayStartCycleEvent * flexRayStartCycleEvent = new FlexRayStartCycleEvent;
        flexRayStartCycleEvent->time = std::stod(match[1]);
        flexRayStartCycleEvent->clusterNr = std::stoul(match[2]);
        flexRayStartCycleEvent->clientId = std::stoul(match[3]);
        flexRayStartCycleEvent->channelNr = std::stoul(match[4]);
        flexRayStartCycleEvent->channelMask = std::stoul(match[5]);
        flexRayStartCycleEvent->cycleNo = std::stoul(match[6]);
        flexRayStartCycleEvent->direction = match[7];
        flexRayStartCycleEvent->ccType = std::stoul(match[8]);
        flexRayStartCycleEvent->ccData[0] = std::stoul(match[9]);
        flexRayStartCycleEvent->ccData[1] = std::stoul(match[10]);
        flexRayStartCycleEvent->ccData[2] = std::stoul(match[11]);
        flexRayStartCycleEvent->ccData[3] = std::stoul(match[12]);
        flexRayStartCycleEvent->ccData[4] = std::stoul(match[13]);
        flexRayStartCycleEvent->nmVectL = std::stoul(match[14]);
        std::istringstream iss(match[15]);
        for (uint8_t i = 0; i < flexRayStartCycleEvent->nmVectL; ++i) {
            unsigned short s;
            iss >> s;
            flexRayStartCycleEvent->nmVect[i] = s;
        }
        return flexRayStartCycleEvent;
    }

    return nullptr;
}

void FlexRayStartCycleEvent::write(File & file, std::ostream & stream)
{
}

}
}
