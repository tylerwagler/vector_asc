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
#include "EthernetStatus.h"
#include "SymbolsRegEx.h"

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
    brClockMode()
{
    eventType = EventType::EthernetStatus;
}

EthernetStatus::~EthernetStatus()
{
}

EthernetStatus * EthernetStatus::parse(File & file, std::string & line)
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
        ethernetStatus->channel = std::stoul(match[2], nullptr, file.base);
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
}

}
}
