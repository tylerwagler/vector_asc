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
#include <sstream>

#include <Vector/ASC/Most25Packet.h>
#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

Most25Packet * Most25Packet::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "Pkt:" REGEX_ws REGEX_MOST_Dir
                     REGEX_WS REGEX_MOST_SourceAdr REGEX_WS REGEX_MOST_DestAdr REGEX_WS REGEX_MOST_PktState
                     REGEX_WS REGEX_MOST_TransferType REGEX_WS REGEX_MOST_PktPrio REGEX_WS REGEX_MOST_PktArbitr
                     REGEX_WS REGEX_MOST_CRC2 REGEX_WS REGEX_MOST_PktLen
                     "((" REGEX_WS REGEX_MOST_Dx")+)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * most25Packet = new Most25Packet;
        most25Packet->time = std::stod(match[1]);
        most25Packet->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
            most25Packet->dir = Dir::Rx;
        else if (match[3] == "Tx")
            most25Packet->dir = Dir::Tx;
        most25Packet->sourceAdr = std::stoul(match[4], nullptr, 16);
        most25Packet->destAdr = std::stoul(match[5], nullptr, 16);
        most25Packet->pktState = std::stoul(match[6], nullptr, 16);
        switch (std::stoul(match[7])) {
        case 1:
            most25Packet->transferType = MostTransferType::Node;
            break;
        case 2:
            most25Packet->transferType = MostTransferType::Spy;
            break;
        }
        most25Packet->pktPrio = std::stoul(match[8], nullptr, 16);
        most25Packet->pktArbitr = std::stoul(match[9], nullptr, 16);
        most25Packet->crc2 = std::stoul(match[10], nullptr, 16);
        most25Packet->pktLen = std::stoul(match[11], nullptr, file.base);
        std::istringstream iss(match[12]);
        switch (file.base) {
        case 10:
            iss >> std::dec;
            break;
        case 16:
            iss >> std::hex;
            break;
        }
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            most25Packet->data.push_back(s);
        }
        return most25Packet;
    }

    return nullptr;
}

void Most25Packet::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "Pkt: " */
    stream << "Pkt: ";

    writeMostDir(file, stream, dir);
    writeMostSourceAdr(file, stream, sourceAdr);
    writeMostSourceAdr(file, stream, destAdr);

    /* format: "%02X %02X %1X %02X %04X %4d " */
    /* format: "%02X %02X %1X %02X %04X %03X " */
    stream
            << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) pktState
            << ' ';
    switch (transferType) {
    case MostTransferType::Node:
        stream << "01";
        break;
    case MostTransferType::Spy:
        stream << "02";
        break;
    }
    stream
            << ' '
            << std::setw(1) << std::uppercase << std::hex << (uint16_t) pktPrio
            << ' '
            << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) pktArbitr
            << ' '
            << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << crc2
            << ' ';
    switch (file.base) {
    case 10:
        stream << std::setfill(' ') << std::setw(4) << std::dec << pktLen;
        break;
    case 16:
        stream << std::setfill('0') << std::setw(3) << std::uppercase << std::hex << pktLen;
        break;
    }
    stream << ' ';

    writeMostData(file, stream, data);

    stream << endl;
}

}
}
