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
#include "MostNetStateEvent.h"

namespace Vector {
namespace ASC {

MostNetStateEvent::MostNetStateEvent() :
    Event(),
    time(0.0),
    channel(0),
    netStateOld(0),
    netStateNew(0)
{
    eventType = EventType::MostNetStateEvent;
}

MostNetStateEvent::~MostNetStateEvent()
{
}

MostNetStateEvent * MostNetStateEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " NetState:"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostNetStateEvent * mostNetStateEvent = new MostNetStateEvent;
        mostNetStateEvent->time = std::stod(match[1]);
        mostNetStateEvent->channel = std::stoul(match[2]);
        mostNetStateEvent->netStateOld = std::stoul(match[3]);
        mostNetStateEvent->netStateNew = std::stoul(match[4]);
        return mostNetStateEvent;
    }

    return nullptr;
}

void MostNetStateEvent::write(File & file, std::ostream & stream)
{
}

}
}
