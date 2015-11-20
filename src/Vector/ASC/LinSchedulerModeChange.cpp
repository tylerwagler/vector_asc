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
#include "LinSchedulerModeChange.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

LinSchedulerModeChange::LinSchedulerModeChange() :
    Event(),
    time(0.0),
    channel(0),
    priorSchedulerMode(0),
    nextSchedulerMode(0)
{
    eventType = EventType::LinSchedulerModeChange;
}

LinSchedulerModeChange::~LinSchedulerModeChange()
{
}

LinSchedulerModeChange * LinSchedulerModeChange::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS "SchedModChng"
                     REGEX_WS "prior scheduler mode" REGEX_ws "=" REGEX_ws REGEX_LIN_scheduleTableIndex ","
                     REGEX_ws "next scheduler mode" REGEX_ws "=" REGEX_ws REGEX_LIN_scheduleTableIndex REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinSchedulerModeChange * linSchedulerModeChange = new LinSchedulerModeChange;
        linSchedulerModeChange->time = std::stod(match[1]);
        linSchedulerModeChange->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linSchedulerModeChange->priorSchedulerMode = std::stoul(match[3]);
        linSchedulerModeChange->nextSchedulerMode = std::stoul(match[4]);
        return linSchedulerModeChange;
    }

    return nullptr;
}

void LinSchedulerModeChange::write(File & file, std::ostream & stream)
{
}

}
}
