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
#include <Vector/ASC/EthernetPacket.h>
#include <Vector/ASC/EthernetSymbolsRegEx.h>

namespace Vector {
namespace ASC {

EthernetPacket * EthernetPacket::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Eth_Time REGEX_WS "ETH" REGEX_WS REGEX_Eth_Channel REGEX_WS REGEX_Eth_Dir
                     REGEX_WS REGEX_Eth_DataLen ":" REGEX_Eth_Data REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * ethernetPacket = new EthernetPacket;
        ethernetPacket->time = std::stod(match[1]);
        ethernetPacket->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
            ethernetPacket->dir = Dir::Rx;
        else if (match[3] == "Tx")
            ethernetPacket->dir = Dir::Tx;
        else if (match[3] == "TxRq")
            ethernetPacket->dir = Dir::TxRq;
        ethernetPacket->dataLen = std::stoul(match[4], nullptr, file.base);
        for (auto i = 0; i < match[5].length() / 2; ++i) {
            std::string s;
            s.append(match[5], 2 * i, 2);
            ethernetPacket->data.push_back(std::stoul(s, nullptr, 16));
        }
        return ethernetPacket;
    }

    return nullptr;
}

void EthernetPacket::write(File & file, std::ostream & stream) {
    writeEthTime(file, stream, time);
    stream << ' ';

    /* format: " ETH %d %s" */
    /* format: " ETH * %s" */
    stream << " ETH " << std::dec << (uint16_t) channel << ' ';
    writeEthDir(file, stream, dir);

    switch (file.base) {
    case 10:
        stream << ' ' << std::setfill(' ') << std::setw(4) << std::dec << dataLen << ':';
        break;
    case 16:
        stream << ' ' << std::setfill(' ') << std::setw(3) << std::hex << dataLen << ':';
        break;
    }
    for (EthData d : data)
        stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) d;

    stream << endl;
}

}
}
