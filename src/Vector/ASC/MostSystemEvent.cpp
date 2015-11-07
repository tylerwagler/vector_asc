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
#include "MostSystemEvent.h"

namespace Vector {
namespace ASC {

MostSystemEvent::MostSystemEvent() :
    Event(),
    time(0.0),
    channel(0),
    sysId(0),
    sysValue(0),
    sysValueOld(0)
{
    eventType = EventType::MostSystemEvent;
}

MostSystemEvent::~MostSystemEvent()
{
}

MostSystemEvent * MostSystemEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " System:"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostSystemEvent * mostSystemEvent = new MostSystemEvent;
        mostSystemEvent->time = std::stof(match[1]);
        mostSystemEvent->channel = std::stoul(match[2]);
        mostSystemEvent->sysId = std::stoul(match[3], nullptr, 16);
        mostSystemEvent->sysValue = std::stoul(match[4], nullptr, 16);
        mostSystemEvent->sysValueOld = std::stoul(match[5], nullptr, 16);
        return mostSystemEvent;
    }

    return nullptr;
}

void MostSystemEvent::write(File & file, std::ostream & stream)
{
}

}
}
