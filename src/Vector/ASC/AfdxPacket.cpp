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

#include <Vector/ASC/AfdxPacket.h>
#include <Vector/ASC/EthernetCommon.h>
#include <Vector/ASC/EthernetSymbolsRegEx.h>

namespace Vector {
namespace ASC {

AfdxPacket * AfdxPacket::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Afdx_Time REGEX_WS "AFDX" REGEX_WS REGEX_Afdx_Channel REGEX_WS REGEX_Afdx_Dir
                     REGEX_WS REGEX_Afdx_EthChannel REGEX_WS REGEX_Afdx_Flags REGEX_WS REGEX_Afdx_BAG REGEX_WS
                     REGEX_Afdx_DataLen ":" REGEX_Afdx_Data REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * afdxPacket = new AfdxPacket;
        afdxPacket->time = std::stod(match[1]);
        afdxPacket->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
            afdxPacket->dir = Dir::Rx;
        else if (match[3] == "Tx")
            afdxPacket->dir = Dir::Tx;
        else if (match[3] == "TxRq")
            afdxPacket->dir = Dir::TxRq;
        afdxPacket->ethChannel = std::stoul(match[4], nullptr, file.base);
        afdxPacket->flags = std::stoul(match[5], nullptr, file.base);
        afdxPacket->bag = std::stoul(match[6], nullptr, file.base);
        afdxPacket->dataLen = std::stoul(match[7], nullptr, file.base);
        for (auto i = 0; i < match[8].length() / 2; ++i) {
            std::string s;
            s.append(match[8], 2 * i, 2);
            afdxPacket->data.push_back(std::stoul(s, nullptr, 16));
        }
        return afdxPacket;
    }

    return nullptr;
}

void AfdxPacket::write(File & file, std::ostream & stream) {
    writeAfdxTime(file, stream, time);
    stream << ' ';

    switch (file.base) {
    case 10:
        /* format: " AFDX %d %s %d %d %d" */
        /* format: " AFDX * %s %d %d %d" */
        stream
                << " AFDX "
                << std::dec << (uint16_t) channel
                << ' ';
        writeAfdxDir(file, stream, dir);
        stream
                << ' ' << std::dec << (uint16_t) ethChannel
                << ' ' << std::dec << flags
                << ' ' << std::dec << bag;

        /* format: " %d:" */
        stream
                << ' ' << std::dec << dataLen << ':';

        break;

    case 16:
        /* format: " AFDX %d %s %4x %4x %4x" */
        /* format: " AFDX * %s %4x %4x %4x" */
        stream
                << " AFDX "
                << std::dec << (uint16_t) channel
                << ' ';
        writeAfdxDir(file, stream, dir);
        stream
                << ' ' << std::setw(4) << std::hex << (uint16_t) ethChannel
                << ' ' << std::setw(4) << std::hex << flags
                << ' ' << std::setw(4) << std::hex << bag;

        /* format: " %4x:" */
        stream
                << ' ' << std::setw(4) << std::hex << dataLen << ':';

        break;
    }

    for (AfdxData d : data)
        stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) d;

    stream << endl;
}

}
}
