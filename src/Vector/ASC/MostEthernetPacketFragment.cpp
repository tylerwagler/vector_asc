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
#include <Vector/ASC/MostEthernetPacketFragment.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostEthernetPacketFragment * MostEthernetPacketFragment::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "PktEthFrg:"
                     REGEX_ws REGEX_MOST_FrgMask REGEX_WS REGEX_MOST_SourceMacAdr REGEX_WS REGEX_MOST_DestMacAdr
                     REGEX_WS REGEX_MOST_AckNack REGEX_WS REGEX_MOST_Pack REGEX_WS REGEX_MOST_CRC4
                     REGEX_WS REGEX_MOST_Cack REGEX_WS REGEX_MOST_RsvdUL REGEX_WS REGEX_MOST_FrgDataLen
                     REGEX_WS REGEX_MOST_FrgDataLenAnnounced REGEX_WS REGEX_MOST_FirstDataLen
                     "((" REGEX_WS REGEX_MOST_Dx ")+)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostEthernetPacketFragment = new MostEthernetPacketFragment;
        mostEthernetPacketFragment->time = std::stod(match[1]);
        mostEthernetPacketFragment->channel = std::stoul(match[2]);
        mostEthernetPacketFragment->frgMask = std::stoul(match[3], nullptr, 16);
        mostEthernetPacketFragment->sourceMacAdr = std::stoul(match[4], nullptr, 16);
        mostEthernetPacketFragment->destMacAdr = std::stoul(match[5], nullptr, 16);
        mostEthernetPacketFragment->ackNack = std::stoul(match[6], nullptr, 16);
        mostEthernetPacketFragment->pAck = std::stoul(match[7], nullptr, 16);
        mostEthernetPacketFragment->crc4 = std::stoul(match[8], nullptr, 16);
        mostEthernetPacketFragment->cAck = std::stoul(match[9], nullptr, 16);
        mostEthernetPacketFragment->rsvdUl = std::stoul(match[10], nullptr, 16);
        mostEthernetPacketFragment->frgDataLen = std::stoul(match[11], nullptr, 16);
        mostEthernetPacketFragment->frgDataLenAnnounced = std::stoul(match[12], nullptr, 16);
        mostEthernetPacketFragment->firstDataLen = std::stoul(match[13], nullptr, 16);
        std::istringstream iss(match[14]);
        iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            mostEthernetPacketFragment->data.push_back(s);
        }
        return mostEthernetPacketFragment;
    }

    return nullptr;
}

void MostEthernetPacketFragment::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "PktEthFrg: " */
    stream << "PktEthFrg: ";

    writeMostFrgMask(file, stream, frgMask);
    writeMostSourceMacAdr(file, stream, sourceMacAdr);
    writeMostDestMacAdr(file, stream, destMacAdr);
    writeMostAckNack(file, stream, ackNack);
    writeMostPAck(file, stream, pAck);
    writeMostCrc4(file, stream, crc4);
    writeMostCAck(file, stream, cAck);
    writeMostRsvdUl(file, stream, rsvdUl);
    writeMostFrgDataLen(file, stream, frgDataLen);
    writeMostFrgDataLenAnnounced(file, stream, frgDataLenAnnounced);
    writeMostFirstDataLen(file, stream, firstDataLen);
    writeMostData(file, stream, data);

    stream << endl;
}

}
}
