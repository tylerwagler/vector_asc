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
#include "MostDataLostEvent.h"

namespace Vector {
namespace ASC {

MostDataLostEvent::MostDataLostEvent() :
    Event(),
    time(0.0),
    channel(0),
    dlInfo(0),
    dlCtrl(0),
    dlAsync(0),
    dlTime1(0.0),
    dlTime2(0.0)
{
    eventType = EventType::MostDataLostEvent;
}

MostDataLostEvent::~MostDataLostEvent()
{
}

MostDataLostEvent * MostDataLostEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " DataLost:"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:digit:].]+)"
                " ([[:digit:].]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostDataLostEvent * mostDataLostEvent = new MostDataLostEvent;
        mostDataLostEvent->time = std::stof(match[1]);
        mostDataLostEvent->channel = std::stoul(match[2]);
        mostDataLostEvent->dlInfo = std::stoul(match[3], nullptr, 16);
        mostDataLostEvent->dlCtrl = std::stoul(match[4], nullptr, 16);
        mostDataLostEvent->dlAsync = std::stoul(match[5], nullptr, 16);
        mostDataLostEvent->dlTime1 = std::stof(match[6]);
        mostDataLostEvent->dlTime2 = std::stof(match[7]);
        return mostDataLostEvent;
    }

    return nullptr;
}

void MostDataLostEvent::write(File & file, std::ostream & stream)
{
}

}
}
