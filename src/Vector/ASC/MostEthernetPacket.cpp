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

#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostEthernetPacket.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostEthernetPacket * MostEthernetPacket::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "PktEth:"
                     REGEX_ws REGEX_MOST_Dir REGEX_WS REGEX_MOST_SourceMacAdr REGEX_WS REGEX_MOST_DestMacAdr
                     REGEX_WS REGEX_MOST_State REGEX_WS REGEX_MOST_AckNack REGEX_WS REGEX_MOST_TransferType
                     REGEX_WS REGEX_MOST_Pack REGEX_WS REGEX_MOST_CRC4 REGEX_WS REGEX_MOST_Cack
                     REGEX_WS REGEX_MOST_RsvdUL
                     REGEX_WS REGEX_MOST_PktEthLen "((" REGEX_WS REGEX_MOST_Dx ")+)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostEthernetPacket = new MostEthernetPacket;
        mostEthernetPacket->time = std::stod(match[1]);
        mostEthernetPacket->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
            mostEthernetPacket->dir = Dir::Rx;
        else if (match[3] == "Tx")
            mostEthernetPacket->dir = Dir::Tx;
        mostEthernetPacket->sourceMacAdr = std::stoul(match[4], nullptr, 16);
        mostEthernetPacket->destMacAdr = std::stoul(match[5], nullptr, 16);
        mostEthernetPacket->state = std::stoul(match[6], nullptr, 16);
        mostEthernetPacket->ackNack = std::stoul(match[7], nullptr, 16);
        switch (std::stoul(match[8])) {
        case 1:
            mostEthernetPacket->transferType = MostTransferType::Node;
            break;
        case 2:
            mostEthernetPacket->transferType = MostTransferType::Spy;
            break;
        }
        mostEthernetPacket->pAck = std::stoul(match[9], nullptr, 16);
        mostEthernetPacket->crc4 = std::stoul(match[10], nullptr, 16);
        mostEthernetPacket->cAck = std::stoul(match[11], nullptr, 16);
        mostEthernetPacket->rsvdUl = std::stoul(match[12], nullptr, 16);
        mostEthernetPacket->pktEthLen = std::stoul(match[13], nullptr, 16);
        std::istringstream iss(match[14]);
        iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            mostEthernetPacket->data.push_back(s);
        }
        return mostEthernetPacket;
    }

    return nullptr;
}

void MostEthernetPacket::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "PktEth: " */
    stream << "PktEth: ";

    writeMostDir(file, stream, dir);
    writeMostSourceMacAdr(file, stream, sourceMacAdr);
    writeMostDestMacAdr(file, stream, destMacAdr);
    writeMostState(file, stream, state);
    writeMostAckNack(file, stream, ackNack);
    writeMostTransferType(file, stream, transferType);
    writeMostPAck(file, stream, pAck);
    writeMostCrc4(file, stream, crc4);
    writeMostCAck(file, stream, cAck);
    writeMostRsvdUl(file, stream, rsvdUl);
    writeMostPktEthLen(file, stream, pktEthLen);
    writeMostData(file, stream, data);

    stream << endl;
}

}
}
