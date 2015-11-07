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
#include "MostStatisticExtendedEvent.h"

namespace Vector {
namespace ASC {

MostStatisticExtendedEvent::MostStatisticExtendedEvent() :
    Event(),
    time(0.0),
    channel(0),
    codingErrors(0),
    frameCounter(0)
{
    eventType = EventType::MostStatisticExtendedEvent;
}

MostStatisticExtendedEvent::~MostStatisticExtendedEvent()
{
}

MostStatisticExtendedEvent * MostStatisticExtendedEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " StatEx:"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostStatisticExtendedEvent * mostStatisticExtendedEvent = new MostStatisticExtendedEvent;
        mostStatisticExtendedEvent->time = std::stof(match[1]);
        mostStatisticExtendedEvent->channel = std::stoul(match[2]);
        mostStatisticExtendedEvent->codingErrors = std::stoul(match[3], nullptr, 16);
        mostStatisticExtendedEvent->frameCounter = std::stoul(match[4], nullptr, 16);
        return mostStatisticExtendedEvent;
    }

    return nullptr;
}

void MostStatisticExtendedEvent::write(File & file, std::ostream & stream)
{
}

}
}
