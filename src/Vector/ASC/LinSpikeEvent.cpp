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
#include "LinSpikeEvent.h"

namespace Vector {
namespace ASC {

LinSpikeEvent::LinSpikeEvent() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    spikeLength(0),
    startOfFrame(0),
    baudrate(0)
{
    eventType = EventType::LinSpikeEvent;
}

LinSpikeEvent::~LinSpikeEvent()
{
}

LinSpikeEvent * LinSpikeEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:digit:]]+)"
                " Spike"
                " (Rx|Tx)"
                " ([[:digit:]]+) microseconds"
                "( SOF = ([[:digit:].]+))?"
                "( BR = ([[:digit:]]+))?$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinSpikeEvent * linSpikeEvent = new LinSpikeEvent;
        linSpikeEvent->time = std::stod(match[1]);
        linSpikeEvent->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
            linSpikeEvent->dir = Dir::Rx;
        else
        if (match[3] == "Tx")
            linSpikeEvent->dir = Dir::Tx;
        linSpikeEvent->spikeLength = std::stoul(match[4]);
        linSpikeEvent->startOfFrame = std::stod(match[6]);
        linSpikeEvent->baudrate = std::stoul(match[8]);
        return linSpikeEvent;
    }

    return nullptr;
}

void LinSpikeEvent::write(File & file, std::ostream & stream)
{
}

}
}
