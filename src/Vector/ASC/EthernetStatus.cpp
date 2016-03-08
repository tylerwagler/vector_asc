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

#include <iomanip>
#include <regex>
#include "EthernetCommon.h"
#include "EthernetStatus.h"
#include "EthernetSymbolsRegEx.h"

namespace Vector {
namespace ASC {

EthernetStatus::EthernetStatus() :
    Event(),
    time(0.0),
    channel(0),
    link(),
    linkSpeed(),
    physical(),
    duplex(),
    mdi(),
    connector(),
    brClockMode(),
    brPairs()
{
    eventType = EventType::EthernetStatus;
}

EthernetStatus * EthernetStatus::read(File & /*file*/, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Eth_Time REGEX_WS "ETH" REGEX_WS REGEX_Eth_Channel REGEX_WS "STAT"
                     REGEX_WS "Link:" REGEX_ws "(.+?)"
                     REGEX_WS "LinkSpeed:" REGEX_ws "(.+?)"
                     REGEX_WS "Physical:" REGEX_ws "(.+?)"
                     REGEX_WS "Duplex:" REGEX_ws "(.+?)"
                     REGEX_WS "MDI:" REGEX_ws "(.+?)"
                     REGEX_WS "Connector:" REGEX_ws "(.+?)"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        EthernetStatus * ethernetStatus = new EthernetStatus;
        ethernetStatus->time = std::stod(match[1]);
        ethernetStatus->channel = std::stoul(match[2]);
        ethernetStatus->link = match[3];
        ethernetStatus->linkSpeed = match[4];
        ethernetStatus->physical = match[5];
        ethernetStatus->duplex = match[6];
        ethernetStatus->mdi = match[7];
        ethernetStatus->connector = match[8];
        return ethernetStatus;
    }

    return nullptr;
}

void EthernetStatus::write(File & file, std::ostream & stream)
{
    writeEthTime(file, stream, time);
    stream << ' ';

    /* format: "ETH ", "ETH *" */
    stream << "ETH ";
    stream << std::dec << (uint16_t) channel;

    /* format: " STAT" */
    stream << " STAT";

    /* format: " Link:" */
    stream << " Link:";
    /* format: "Link_up", "Link_error", "Negotiate_link", "Link_down" */
    stream << link;

    /* format: " LinkSpeed:" */
    stream << " LinkSpeed:";
    /* format: "Mbit/s" */
    stream << linkSpeed;

    /* format: " Physical:" */
    stream << " Physical:";
    /* format: "IEEE802.3", "BroadR-Reach" */
    stream << physical;

    /* format: " Duplex:" */
    stream << " Duplex:";
    /* format: "Full", "Half" */
    stream << duplex;

    /* format: " MDI:" */
    stream << " MDI:";
    /* format: "Crossover", "Direct" */
    stream << mdi;

    /* format: " Connector:" */
    stream << " Connector:";
    /* format: "RJ45", "D-Sub" */
    stream << connector;

    if (physical == "BroadR-Reach") {
        /* format: " BRClockMode:" */
        stream << " BRClockMode:";
        /* format: "Master", "Slave" */
        stream << brClockMode;

        /* format: " BrPairs:" */
        stream << " BrPairs:";
        /* format: "1-pair", "2-pair", "4-pair" */
        stream << brPairs;
    }

    stream << endl;
}

}
}
