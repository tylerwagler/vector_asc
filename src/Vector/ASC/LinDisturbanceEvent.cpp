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
#include "LinDisturbanceEvent.h"

namespace Vector {
namespace ASC {

LinDisturbanceEvent::LinDisturbanceEvent() :
    Event(),
    time(0.0),
    channel(),
    disturbanceType(),
    byteIndex(0),
    bitIndex(0),
    bitOffset(0),
    length(0),
    header(0),
    disturbingHeader(0)
{
    eventType = EventType::LinDisturbanceEvent;
}

LinDisturbanceEvent::~LinDisturbanceEvent()
{
}

LinDisturbanceEvent * LinDisturbanceEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " DisturbanceEvent"
                " Type = (.+)"
                " ByteIndex = ([[:digit:]]+)"
                " BitIndex = ([[:digit:]]+)"
                " BitOffset = ([[:digit:]]+)"
                " Length = ([[:digit:]]+)"
                " Header = ([[:xdigit:]]+)"
                " Disturbing header = ([[:xdigit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinDisturbanceEvent * linDisturbanceEvent = new LinDisturbanceEvent;
        linDisturbanceEvent->time = std::stof(match[1]);
        linDisturbanceEvent->channel = match[2];
        linDisturbanceEvent->disturbanceType = match[3];
        linDisturbanceEvent->byteIndex = std::stoul(match[4]);
        linDisturbanceEvent->bitIndex = std::stoul(match[5]);
        linDisturbanceEvent->bitOffset = std::stoul(match[6]);
        linDisturbanceEvent->length = std::stoul(match[7]);
        linDisturbanceEvent->header = std::stoul(match[8], nullptr, 16);
        linDisturbanceEvent->disturbingHeader = std::stoul(match[9], nullptr, 16);
        return linDisturbanceEvent;
    }

    return nullptr;
}

void LinDisturbanceEvent::write(File & file, std::ostream & stream)
{
}

}
}
