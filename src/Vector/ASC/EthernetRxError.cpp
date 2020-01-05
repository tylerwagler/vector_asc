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
#include <Vector/ASC/EthernetRxError.h>
#include <Vector/ASC/EthernetSymbolsRegEx.h>

namespace Vector {
namespace ASC {

EthernetRxError * EthernetRxError::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Eth_Time REGEX_WS "ETH" REGEX_WS REGEX_Eth_Channel REGEX_WS "RxEr"
                     REGEX_WS REGEX_Eth_ErrorCode REGEX_WS REGEX_Eth_FrameChecksum
                     REGEX_WS REGEX_Eth_DataLen ":" REGEX_Eth_Data REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * ethernetRxError = new EthernetRxError;
        ethernetRxError->time = std::stod(match[1]);
        ethernetRxError->channel = std::stoul(match[2]);
        ethernetRxError->errorCode = std::stoul(match[3], nullptr, file.base);
        ethernetRxError->frameChecksum = std::stoul(match[4], nullptr, 16);
        ethernetRxError->dataLen = std::stoul(match[5], nullptr, file.base);
        for (auto i = 0; i < match[6].length() / 2; ++i) {
            std::string s;
            s.append(match[6], 2 * i, 2);
            ethernetRxError->data.push_back(std::stoul(s, nullptr, 16));
        }
        return ethernetRxError;
    }

    return nullptr;
}

void EthernetRxError::write(File & file, std::ostream & stream) {
    writeEthTime(file, stream, time);
    stream << ' ';

    /* format: " ETH %d RxEr %02x %08x" */
    /* format: " ETH * RxEr %02x %08x" */
    stream
            << " ETH "
            << std::dec << (uint16_t) channel
            << " RxEr "
            << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) errorCode
            << ' '
            << std::setfill('0') << std::setw(8) << std::hex << frameChecksum;

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
