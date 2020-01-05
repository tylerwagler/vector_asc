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

#include <Vector/ASC/Most150Packet.h>
#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

Most150Packet * Most150Packet::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "Pkt150:"
                     REGEX_ws REGEX_MOST_Dir REGEX_WS REGEX_MOST_SourceAdr REGEX_WS REGEX_MOST_DestAdr
                     REGEX_WS REGEX_MOST_State REGEX_WS REGEX_MOST_AckNack REGEX_WS REGEX_MOST_TransferType
                     REGEX_WS REGEX_MOST_Pack REGEX_WS REGEX_MOST_RsvdUC REGEX_WS REGEX_MOST_Pindex
                     REGEX_WS REGEX_MOST_CRC2 REGEX_WS REGEX_MOST_Cack REGEX_WS REGEX_MOST_RsvdUL
                     REGEX_WS REGEX_MOST_Pkt150Len "((" REGEX_WS REGEX_MOST_Dx ")+)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * most150Packet = new Most150Packet;
        most150Packet->time = std::stod(match[1]);
        most150Packet->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
            most150Packet->dir = Dir::Rx;
        else if (match[3] == "Tx")
            most150Packet->dir = Dir::Tx;
        most150Packet->sourceAdr = std::stoul(match[4], nullptr, 16);
        most150Packet->destAdr = std::stoul(match[5], nullptr, 16);
        most150Packet->state = std::stoul(match[6], nullptr, 16);
        most150Packet->ackNack = std::stoul(match[7], nullptr, 16);
        switch (std::stoul(match[16])) {
        case 1:
            most150Packet->transferType = MostTransferType::Node;
            break;
        case 2:
            most150Packet->transferType = MostTransferType::Spy;
            break;
        }
        most150Packet->pAck = std::stoul(match[9], nullptr, 16);
        most150Packet->rsvdUc = std::stoul(match[10], nullptr, 16);
        most150Packet->pIndex = std::stoul(match[11], nullptr, 16);
        most150Packet->crc2 = std::stoul(match[12], nullptr, 16);
        most150Packet->cAck = std::stoul(match[13], nullptr, 16);
        most150Packet->rsvdUl = std::stoul(match[14], nullptr, 16);
        most150Packet->pkt150Len = std::stoul(match[15], nullptr, 16);
        std::istringstream iss(match[16]);
        iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            most150Packet->data.push_back(s);
        }
        return most150Packet;
    }

    return nullptr;
}

void Most150Packet::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "Pkt150: " */
    stream << "Pkt150: ";

    writeMostDir(file, stream, dir);
    writeMostSourceAdr(file, stream, sourceAdr);
    writeMostDestAdr(file, stream, destAdr);
    writeMostState(file, stream, state);
    writeMostAckNack(file, stream, ackNack);
    writeMostTransferType(file, stream, transferType);
    writeMostPAck(file, stream, pAck);
    writeMostRsvdUc(file, stream, rsvdUc);
    writeMostPIndex(file, stream, pIndex);
    writeMostCrc2(file, stream, crc2);
    writeMostCAck(file, stream, cAck);
    writeMostRsvdUl(file, stream, rsvdUl);
    writeMostPkt150Len(file, stream, pkt150Len);
    writeMostData(file, stream, data);

    stream << endl;
}

}
}
