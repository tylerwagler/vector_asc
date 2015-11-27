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
#include "FlexRayCommon.h"
#include "FlexRayStatusEvent.h"
#include "FlexRaySymbolsRegEx.h"

namespace Vector {
namespace ASC {

FlexRayStatusEvent::FlexRayStatusEvent() :
    Event(),
    time(0.0),
    clusterNr(0),
    clientId(0),
    channelNr(0),
    channelMask(0),
    cycleNo(0),
    ccType(0),
    syncState(0),
    ccData(),
    symbol(0),
    wakeUpState(0),
    spyFlag(false)
{
    eventType = EventType::FlexRayStatusEvent;
}

FlexRayStatusEvent::~FlexRayStatusEvent()
{
}

FlexRayStatusEvent * FlexRayStatusEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "SE"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([012])"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([01234])" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([01])" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayStatusEvent * flexRayStatusEvent = new FlexRayStatusEvent;
        flexRayStatusEvent->time = std::stod(match[1]);
        flexRayStatusEvent->clusterNr = std::stoul(match[2]);
        flexRayStatusEvent->clientId = std::stoul(match[3]);
        flexRayStatusEvent->channelNr = std::stoul(match[4]);
        flexRayStatusEvent->channelMask = std::stoul(match[5]);
        flexRayStatusEvent->cycleNo = std::stoul(match[6]);
        flexRayStatusEvent->ccType = std::stoul(match[7]);
        flexRayStatusEvent->syncState = std::stoul(match[8]);
        flexRayStatusEvent->ccData[0] = std::stoul(match[9]);
        flexRayStatusEvent->ccData[1] = std::stoul(match[10]);
        flexRayStatusEvent->symbol = std::stoul(match[11]);
        flexRayStatusEvent->wakeUpState = std::stoul(match[12]);
        flexRayStatusEvent->spyFlag = (match[13] == '1');
        return flexRayStatusEvent;
    }

    return nullptr;
}

void FlexRayStatusEvent::write(File & file, std::ostream & stream)
{
    stream << endl;
}

}
}
