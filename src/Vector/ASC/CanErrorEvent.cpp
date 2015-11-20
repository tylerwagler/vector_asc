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
#include "CanErrorEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanErrorEvent::CanErrorEvent() :
    Event(),
    time(0.0),
    channel(0),
    error()
{
    eventType = EventType::CanErrorEvent;
}

CanErrorEvent::~CanErrorEvent()
{
}

CanErrorEvent * CanErrorEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time  REGEX_WS "CAN" REGEX_WS  REGEX_Channel REGEX_WS "Status:" REGEX_ws REGEX_Error REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanErrorEvent * canErrorEvent = new CanErrorEvent;
        canErrorEvent->time = std::stod(match[1]);
        canErrorEvent->channel = std::stoul(match[2]);
        canErrorEvent->error = match[3];
        return canErrorEvent;
    }

    return nullptr;
}

void CanErrorEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << " CAN " << channel
            << " Status:" << error
            << endl;
}

}
}
