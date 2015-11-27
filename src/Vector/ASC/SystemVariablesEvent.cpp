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
#include "CanCommon.h"
#include "CanSymbolsRegEx.h"
#include "SystemVariablesEvent.h"

namespace Vector {
namespace ASC {

SystemVariablesEvent::SystemVariablesEvent() :
    Event(),
    time(0.0),
    svtype(),
    flag(),
    path(),
    value()
{
    eventType = EventType::SystemVariablesEvent;
}

SystemVariablesEvent::~SystemVariablesEvent()
{
}

SystemVariablesEvent * SystemVariablesEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "SV:" REGEX_ws REGEX_svtype REGEX_WS "0" REGEX_WS "0"
                     REGEX_WS "(.+?)" REGEX_ws "=" REGEX_ws "(.+?)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        SystemVariablesEvent * systemVariablesEvent = new SystemVariablesEvent;
        systemVariablesEvent->time = std::stod(match[1]);
        switch (std::stoul(match[2])) {
        case 1:
            systemVariablesEvent->svtype = Svtype::Float;
            break;
        case 2:
            systemVariablesEvent->svtype = Svtype::Int;
            break;
        case 3:
            systemVariablesEvent->svtype = Svtype::String;
            break;
        case 4:
            systemVariablesEvent->svtype = Svtype::FloatArray;
            break;
        case 5:
            systemVariablesEvent->svtype = Svtype::IntArray;
            break;
        }
        systemVariablesEvent->path = match[3];
        systemVariablesEvent->value = match[4];
        return systemVariablesEvent;
    }

    return nullptr;
}

void SystemVariablesEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << ' ' << (uint32_t) svtype
            << ' ' << (flag[0] ? '1' : '0')
            << ' ' << (flag[1] ? '1' : '0')
            << ' ' << path
            << " = " << value;

    stream << endl;
}

}
}
