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

#include <Vector/ASC/EthernetCommon.h>
#include <Vector/ASC/EthernetStatus.h>
#include <Vector/ASC/EthernetSymbolsRegEx.h>

namespace Vector {
namespace ASC {

EthernetStatus * EthernetStatus::read(File & /*file*/, std::string & line) {
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
        auto * ethernetStatus = new EthernetStatus;
        ethernetStatus->time = std::stod(match[1]);
        ethernetStatus->channel = std::stoul(match[2]);
        if (match[3] == "Link_up")
            ethernetStatus->link = EthernetStatus::Link::Up;
        else if (match[3] == "Link_error")
            ethernetStatus->link = EthernetStatus::Link::Error;
        else if (match[3] == "Negotiate_link")
            ethernetStatus->link = EthernetStatus::Link::Negotiate;
        else if (match[3] == "Link_down")
            ethernetStatus->link = EthernetStatus::Link::Down;
        else
            ethernetStatus->link = EthernetStatus::Link::Unknown;
        ethernetStatus->linkSpeed = std::stoul(match[4]);
        if (match[5] == "IEEE802.3")
            ethernetStatus->physical = EthernetStatus::Physical::Ieee802_3;
        else if (match[5] == "BroadR_Reach")
            ethernetStatus->physical = EthernetStatus::Physical::BroadR_Reach;
        else
            ethernetStatus->physical = EthernetStatus::Physical::Unknown;
        if (match[6] == "Full")
            ethernetStatus->duplex = EthernetStatus::Duplex::Full;
        else if (match[6] == "Half")
            ethernetStatus->duplex = EthernetStatus::Duplex::Half;
        else
            ethernetStatus->duplex = EthernetStatus::Duplex::Unknown;
        if (match[7] == "Crossover")
            ethernetStatus->mdi = EthernetStatus::Mdi::Crossover;
        else if (match[7] == "Direct")
            ethernetStatus->mdi = EthernetStatus::Mdi::Direct;
        else
            ethernetStatus->mdi = EthernetStatus::Mdi::Unknown;
        if (match[8] == "RJ45")
            ethernetStatus->connector = EthernetStatus::Connector::Rj45;
        else if (match[8] == "D-Sub")
            ethernetStatus->connector = EthernetStatus::Connector::DSub;
        else
            ethernetStatus->connector = EthernetStatus::Connector::Unknown;
        return ethernetStatus;
    }

    return nullptr;
}

void EthernetStatus::write(File & file, std::ostream & stream) {
    writeEthTime(file, stream, time);
    stream << ' ';

    /* format: "ETH ", "ETH *" */
    stream << "ETH ";
    stream << std::dec << static_cast<uint16_t>(channel);

    /* format: " STAT" */
    stream << " STAT";

    /* format: " Link:" */
    stream << " Link:";
    /* format: "Link_up", "Link_error", "Negotiate_link", "Link_down" */
    switch (link) {
    case Link::Unknown:
        break;
    case Link::Up:
        stream << "Link_up";
        break;
    case Link::Error:
        stream << "Link_error";
        break;
    case Link::Negotiate:
        stream << "Negotiate_link";
        break;
    case Link::Down:
        stream << "Link_down";
        break;
    }

    /* format: " LinkSpeed:" */
    stream << " LinkSpeed:";
    /* format: "Mbit/s" */
    stream << linkSpeed << "Mbit/s";

    /* format: " Physical:" */
    stream << " Physical:";
    /* format: "IEEE802.3", "BroadR-Reach" */
    switch (physical) {
    case Physical::Unknown:
        break;
    case Physical::Ieee802_3:
        stream << "IEEE802.3";
        break;
    case Physical::BroadR_Reach:
        stream << "BroadR_Reach";
        break;
    }

    /* format: " Duplex:" */
    stream << " Duplex:";
    /* format: "Full", "Half" */
    switch (duplex) {
    case Duplex::Unknown:
        break;
    case Duplex::Full:
        stream << "Full";
        break;
    case Duplex::Half:
        stream << "Half";
        break;
    }

    /* format: " MDI:" */
    stream << " MDI:";
    /* format: "Crossover", "Direct" */
    switch (mdi) {
    case Mdi::Unknown:
        break;
    case Mdi::Crossover:
        stream << "Crossover";
        break;
    case Mdi::Direct:
        stream << "Direct";
        break;
    }

    /* format: " Connector:" */
    stream << " Connector:";
    /* format: "RJ45", "D-Sub" */
    switch (connector) {
    case Connector::Unknown:
        break;
    case Connector::Rj45:
        stream << "RJ45";
        break;
    case Connector::DSub:
        stream << "D-Sub";
        break;
    }

    if (physical == Physical::BroadR_Reach) {
        /* format: " BRClockMode:" */
        stream << " BRClockMode:";
        /* format: "Master", "Slave" */
        switch (brClockMode) {
        case BRClockMode::Unknown:
            break;
        case BRClockMode::Master:
            stream << "Master";
            break;
        case BRClockMode::Slave:
            stream << "Slave";
            break;
        }

        /* format: " BrPairs:" */
        stream << " BrPairs:";
        /* format: "1-pair", "2-pair", "4-pair" */
        switch (brPairs) {
        case BRPairs::Unknown:
            break;
        case BRPairs::BR1Pair:
            stream << "1-pair";
            break;
        case BRPairs::BR2Pair:
            stream << "2-pair";
            break;
        case BRPairs::BR4Pair:
            stream << "4-pair";
            break;
        }
    }

    stream << endl;
}

}
}
