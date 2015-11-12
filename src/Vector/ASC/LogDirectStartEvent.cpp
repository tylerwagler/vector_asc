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
#include "LogDirectStartEvent.h"

namespace Vector {
namespace ASC {

LogDirectStartEvent::LogDirectStartEvent() :
    Event(),
    time(0.0),
    preTrigger(0)
{
    eventType = EventType::LogDirectStartEvent;
}

LogDirectStartEvent::~LogDirectStartEvent()
{
}

LogDirectStartEvent * LogDirectStartEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " log direct start"
                " \\(([[:digit:]]{1,10})ms\\)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LogDirectStartEvent * logDirectStartEvent = new LogDirectStartEvent;
        logDirectStartEvent->time = std::stod(match[1]);
        logDirectStartEvent->preTrigger = std::stoul(match[2]);
        return logDirectStartEvent;
    }

    return nullptr;
}

void LogDirectStartEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << " log direct start ("
            << std::dec << preTrigger << "ms)"
            << endl;
}

}
}
