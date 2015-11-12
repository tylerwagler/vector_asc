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
#include "LogDirectStopEvent.h"

namespace Vector {
namespace ASC {

LogDirectStopEvent::LogDirectStopEvent() :
    Event(),
    time(0.0),
    postTrigger(0)
{
    eventType = EventType::LogDirectStopEvent;
}

LogDirectStopEvent::~LogDirectStopEvent()
{
}

LogDirectStopEvent * LogDirectStopEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " log direct stop"
                " \\(([[:digit:]]{1,10})ms\\)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LogDirectStopEvent * logDirectStopEvent = new LogDirectStopEvent;
        logDirectStopEvent->time = std::stod(match[1]);
        logDirectStopEvent->postTrigger = std::stoul(match[2]);
        return logDirectStopEvent;
    }

    return nullptr;
}

void LogDirectStopEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << " log direct stop ("
            << std::dec << postTrigger << "ms)"
            << endl;
}

}
}
