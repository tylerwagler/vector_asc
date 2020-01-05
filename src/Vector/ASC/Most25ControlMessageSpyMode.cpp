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

#include <Vector/ASC/Most25ControlMessageSpyMode.h>
#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

Most25ControlMessageSpyMode * Most25ControlMessageSpyMode::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "Rx"
                     REGEX_WS REGEX_MOST_SourceAdr REGEX_WS REGEX_MOST_DestAdr REGEX_WS REGEX_MOST_RType
                     "((" REGEX_WS REGEX_MOST_Dx "){17})"
                     REGEX_WS REGEX_MOST_State REGEX_WS REGEX_MOST_AckNack REGEX_WS REGEX_MOST_CRC REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * most25ControlMessageSpyMode = new Most25ControlMessageSpyMode;
        most25ControlMessageSpyMode->time = std::stod(match[1]);
        most25ControlMessageSpyMode->channel = std::stoul(match[2]);
        most25ControlMessageSpyMode->sourceAdr = std::stoul(match[3], nullptr, file.base);
        most25ControlMessageSpyMode->destAdr = std::stoul(match[4], nullptr, file.base);
        most25ControlMessageSpyMode->rType = std::stoul(match[5], nullptr, file.base);
        std::istringstream iss(match[6]);
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
            most25ControlMessageSpyMode->data.push_back(s);
        }
        most25ControlMessageSpyMode->state = std::stoul(match[8], nullptr, file.base);
        most25ControlMessageSpyMode->ackNack = std::stoul(match[9], nullptr, file.base);
        most25ControlMessageSpyMode->crc = std::stoul(match[10], nullptr, file.base);
        return most25ControlMessageSpyMode;
    }

    return nullptr;
}

void Most25ControlMessageSpyMode::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);
    writeMostDir(file, stream, Dir::Rx);
    writeMostSourceAdr(file, stream, sourceAdr);
    writeMostDestAdr(file, stream, destAdr);
    writeMostRType(file, stream, rType);
    stream << ' ';
    writeMostData(file, stream, data);
    stream << ' ';
    writeMostState(file, stream, state);
    writeMostAckNack(file, stream, ackNack);
    writeMostCrc(file, stream, crc);

    stream << endl;
}

}
}
