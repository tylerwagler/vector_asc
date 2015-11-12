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
#include "MostHwModeEvent.h"

namespace Vector {
namespace ASC {

MostHwModeEvent::MostHwModeEvent() :
    Event(),
    time(0.0),
    channel(0),
    hwMode(0),
    hwModeMask(0)
{
    eventType = EventType::MostHwModeEvent;
}

MostHwModeEvent::~MostHwModeEvent()
{
}

MostHwModeEvent * MostHwModeEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " HWMode:"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostHwModeEvent * mostHwModeEvent = new MostHwModeEvent;
        mostHwModeEvent->time = std::stod(match[1]);
        mostHwModeEvent->channel = std::stoul(match[2]);
        mostHwModeEvent->hwMode = std::stoul(match[3], nullptr, 16);
        mostHwModeEvent->hwModeMask = std::stoul(match[4], nullptr, 16);
        return mostHwModeEvent;
    }

    return nullptr;
}

void MostHwModeEvent::write(File & file, std::ostream & stream)
{
}

}
}
