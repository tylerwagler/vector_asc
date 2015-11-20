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
#include "CanRemoteFrameEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanRemoteFrameEvent::CanRemoteFrameEvent() :
    Event(),
    time(0.0),
    channel(0),
    id(0),
    dir(Dir::Rx)
{
    eventType = EventType::CanRemoteFrameEvent;
}

CanRemoteFrameEvent::~CanRemoteFrameEvent()
{
}

CanRemoteFrameEvent * CanRemoteFrameEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS REGEX_Channel REGEX_WS REGEX_ID REGEX_WS REGEX_Dir REGEX_WS "r" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanRemoteFrameEvent * canRemoteFrameEvent = new CanRemoteFrameEvent;
        canRemoteFrameEvent->time = std::stod(match[1]);
        canRemoteFrameEvent->channel = std::stoul(match[2]);
        canRemoteFrameEvent->id = std::stoul(match[3], nullptr, 16);
        if (match[4] == "Rx")
                canRemoteFrameEvent->dir = Dir::Rx;
        else
        if (match[4] == "Tx")
                canRemoteFrameEvent->dir = Dir::Tx;
        return canRemoteFrameEvent;
    }

    return nullptr;
}

void CanRemoteFrameEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << ' ' << std::dec << channel
            << ' ' << std::hex << id
            << ' ';
    switch(dir) {
    case Dir::Rx:
        stream << "Rx";
        break;
    case Dir::Tx:
        stream << "Tx";
        break;
    }
    stream << " r" << endl;
}

}
}
