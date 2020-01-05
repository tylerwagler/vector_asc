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

#include <Vector/ASC/Most150ControlMessageFragment.h>
#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

Most150ControlMessageFragment * Most150ControlMessageFragment::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "Msg150Frg:"
                     REGEX_ws REGEX_MOST_FrgMask REGEX_WS REGEX_MOST_SourceAdr REGEX_WS REGEX_MOST_DestAdr
                     REGEX_WS REGEX_MOST_AckNack REGEX_WS REGEX_MOST_PAck REGEX_WS REGEX_MOST_Priority
                     REGEX_WS REGEX_MOST_Pindex REGEX_WS REGEX_MOST_CRC2 REGEX_WS REGEX_MOST_Cack
                     REGEX_WS REGEX_MOST_RsvdUL REGEX_WS REGEX_MOST_FrgDataLen
                     REGEX_WS REGEX_MOST_FrgDataLenAnnounced
                     REGEX_WS REGEX_MOST_FirstDataLen "((" REGEX_WS REGEX_MOST_Dx ")+)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * most150ControlMessageFragment = new Most150ControlMessageFragment;
        most150ControlMessageFragment->time = std::stod(match[1]);
        most150ControlMessageFragment->channel = std::stoul(match[2]);
        most150ControlMessageFragment->frgMask = std::stoul(match[3], nullptr, 16);
        most150ControlMessageFragment->sourceAdr = std::stoul(match[4], nullptr, 16);
        most150ControlMessageFragment->destAdr = std::stoul(match[5], nullptr, 16);
        most150ControlMessageFragment->ackNack = std::stoul(match[6], nullptr, 16);
        most150ControlMessageFragment->pAck = std::stoul(match[7], nullptr, 16);
        most150ControlMessageFragment->priority = std::stoul(match[8], nullptr, 16);
        most150ControlMessageFragment->pIndex = std::stoul(match[9], nullptr, 16);
        most150ControlMessageFragment->crc2 = std::stoul(match[10], nullptr, 16);
        most150ControlMessageFragment->cAck = std::stoul(match[11], nullptr, 16);
        most150ControlMessageFragment->rsvdUl = std::stoul(match[12], nullptr, 16);
        most150ControlMessageFragment->frgDataLen = std::stoul(match[13], nullptr, 16);
        most150ControlMessageFragment->frgDataLenAnnounced = std::stoul(match[14], nullptr, 16);
        most150ControlMessageFragment->firstDataLen = std::stoul(match[15], nullptr, 16);
        std::istringstream iss(match[16]);
        iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            most150ControlMessageFragment->data.push_back(s);
        }
        return most150ControlMessageFragment;
    }

    return nullptr;
}

void Most150ControlMessageFragment::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "Msg150Frg: " */
    stream << "Msg150Frg: ";

    writeMostFrgMask(file, stream, frgMask);
    writeMostSourceAdr(file, stream, sourceAdr);
    writeMostDestAdr(file, stream, destAdr);
    writeMostAckNack(file, stream, ackNack);
    writeMostPAck(file, stream, pAck);
    writeMostPriority(file, stream, priority);
    writeMostPIndex(file, stream, pIndex);
    writeMostCrc2(file, stream, crc2);
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
