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
#include "MostTriggerEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

MostTriggerEvent::MostTriggerEvent() :
    Event(),
    time(0.0),
    channel(0),
    trigMode(MostTrigMode::Unknown),
    trigHw(0),
    trigValue()
{
    eventType = EventType::MostTriggerEvent;
}

MostTriggerEvent::~MostTriggerEvent()
{
}

MostTriggerEvent * MostTriggerEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "Trigger:"
                     REGEX_ws REGEX_MOST_TrigMode REGEX_WS REGEX_MOST_TrigHW REGEX_WS REGEX_MOST_TrigValue
                     REGEX_WS REGEX_MOST_TrigValue REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostTriggerEvent * mostTriggerEvent = new MostTriggerEvent;
        mostTriggerEvent->time = std::stod(match[1]);
        mostTriggerEvent->channel = std::stoul(match[2]);
        switch(std::stoul(match[3])) {
        case 0:
            mostTriggerEvent->trigMode = MostTrigMode::Unknown;
            break;
        case 1:
            mostTriggerEvent->trigMode = MostTrigMode::SynchronizationMaster;
            break;
        case 2:
            mostTriggerEvent->trigMode = MostTrigMode::SynchronizationSlave;
            break;
        }
        mostTriggerEvent->trigHw = std::stoul(match[4]);
        mostTriggerEvent->trigValue[0] = std::stoul(match[5], nullptr, 16);
        mostTriggerEvent->trigValue[1] = std::stoul(match[6], nullptr, 16);
        return mostTriggerEvent;
    }

    return nullptr;
}

void MostTriggerEvent::write(File & file, std::ostream & stream)
{
}

}
}
