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
#include "MostLightLockEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

MostLightLockEvent::MostLightLockEvent() :
    Event(),
    time(0.0),
    channel(0),
    llState(0)
{
    eventType = EventType::MostLightLockEvent;
}

MostLightLockEvent::~MostLightLockEvent()
{
}

MostLightLockEvent * MostLightLockEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "LL:" REGEX_ws REGEX_MOST_LLState REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostLightLockEvent * mostLightLockEvent = new MostLightLockEvent;
        mostLightLockEvent->time = std::stod(match[1]);
        mostLightLockEvent->channel = std::stoul(match[2]);
        mostLightLockEvent->llState = std::stoul(match[3]);
        return mostLightLockEvent;
    }

    return nullptr;
}

void MostLightLockEvent::write(File & file, std::ostream & stream)
{
}

}
}
