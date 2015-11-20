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
#include "CanBusStatisticsEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanBusStatisticsEvent::CanBusStatisticsEvent() :
    Event(),
    time(0.0),
    channel(0),
    dataFrames(0),
    remoteFrames(0),
    extendedDataFrames(0),
    extendedRemoteFrames(0),
    errorFrames(0),
    overloadFrames(0),
    busload(0.0)
{
    eventType = EventType::CanBusStatisticsEvent;
}

CanBusStatisticsEvent::~CanBusStatisticsEvent()
{
}

CanBusStatisticsEvent * CanBusStatisticsEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS REGEX_Channel REGEX_WS "Statistic:"
                     REGEX_WS "D" REGEX_WS REGEX_StatNumber
                     REGEX_WS "R" REGEX_WS REGEX_StatNumber
                     REGEX_WS "XD" REGEX_WS REGEX_StatNumber
                     REGEX_WS "XR" REGEX_WS REGEX_StatNumber
                     REGEX_WS "E" REGEX_WS REGEX_StatNumber
                     REGEX_WS "O" REGEX_WS REGEX_StatNumber
                     REGEX_WS "B" REGEX_WS REGEX_StatPercent "%"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanBusStatisticsEvent * canBusStatisticsEvent = new CanBusStatisticsEvent;
        canBusStatisticsEvent->time = std::stod(match[1]);
        canBusStatisticsEvent->channel = std::stoul(match[2]);
        canBusStatisticsEvent->dataFrames = std::stoul(match[3]);
        canBusStatisticsEvent->remoteFrames = std::stoul(match[4]);
        canBusStatisticsEvent->extendedDataFrames = std::stoul(match[5]);
        canBusStatisticsEvent->extendedRemoteFrames = std::stoul(match[6]);
        canBusStatisticsEvent->errorFrames = std::stoul(match[7]);
        canBusStatisticsEvent->overloadFrames = std::stoul(match[8]);
        canBusStatisticsEvent->busload = std::stod(match[9]);
        return canBusStatisticsEvent;
    }

    return nullptr;
}

void CanBusStatisticsEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << ' ' << std::dec << channel
            << " Statistic:"
            << " D " << dataFrames
            << " R " << remoteFrames
            << " XD " << extendedDataFrames
            << " XR " << extendedRemoteFrames
            << " E " << errorFrames
            << " O " << overloadFrames
            << " B " << busload
            << endl;
}

}
}
