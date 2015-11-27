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
#include "FlexRayErrorEvent.h"
#include "FlexRaySymbolsRegEx.h"

namespace Vector {
namespace ASC {

FlexRayErrorEvent::FlexRayErrorEvent() :
    Event(),
    time(0.0),
    clusterNr(0),
    clientId(0),
    channelNr(0),
    channelMask(0),
    ccType(0),
    ccData()
{
    eventType = EventType::FlexRayErrorEvent;
}

FlexRayErrorEvent::~FlexRayErrorEvent()
{
}

FlexRayErrorEvent * FlexRayErrorEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "EE"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayErrorEvent * flexRayErrorEvent = new FlexRayErrorEvent;
        flexRayErrorEvent->time = std::stod(match[1]);
        flexRayErrorEvent->clusterNr = std::stoul(match[2]);
        flexRayErrorEvent->clientId = std::stoul(match[3]);
        flexRayErrorEvent->channelNr = std::stoul(match[4]);
        flexRayErrorEvent->channelMask = std::stoul(match[5]);
        flexRayErrorEvent->ccType = std::stoul(match[6]);
        flexRayErrorEvent->ccData[0] = std::stoul(match[7]);
        flexRayErrorEvent->ccData[1] = std::stoul(match[8]);
        flexRayErrorEvent->ccData[2] = std::stoul(match[9]);
        flexRayErrorEvent->ccData[3] = std::stoul(match[10]);
        return flexRayErrorEvent;
    }

    return nullptr;
}

void FlexRayErrorEvent::write(File & file, std::ostream & stream)
{
    stream << endl;
}

}
}
