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
#include "GlobalMarkerEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

GlobalMarkerEvent::GlobalMarkerEvent() :
    Event(),
    time(0.0),
    type(0),
    backgroundColor(0),
    foregroundColor(0),
    relocatable(true),
    groupName(),
    markerName(),
    description()
{
    eventType = EventType::GlobalMarkerEvent;
}

GlobalMarkerEvent::~GlobalMarkerEvent()
{
}

GlobalMarkerEvent * GlobalMarkerEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([01])"
                     REGEX_WS "GMGroup:" REGEX_ws "(.+?)"
                     REGEX_WS "GMMarker:" REGEX_ws "(.+?)"
                     REGEX_WS "GMDescription:" REGEX_ws "(.+?)"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        GlobalMarkerEvent * globalMarkerEvent = new GlobalMarkerEvent;
        globalMarkerEvent->time = std::stod(match[1]);
        globalMarkerEvent->type = std::stoul(match[2]);
        globalMarkerEvent->backgroundColor = std::stoul(match[3]);
        globalMarkerEvent->foregroundColor = std::stoul(match[4]);
        globalMarkerEvent->relocatable = (match[5] == '1');
        globalMarkerEvent->groupName = match[6];
        globalMarkerEvent->markerName = match[7];
        globalMarkerEvent->description = match[8];
        return globalMarkerEvent;
    }

    return nullptr;
}

void GlobalMarkerEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << ' ' << std::dec << type
            << ' ' << backgroundColor
            << ' ' << foregroundColor
            << ' ' << (relocatable ? '1' : '0')
            << " GMGroup: " << groupName
            << " GMMarker: " << markerName
            << " GMDescription: " << description
            << endl;
}

}
}
