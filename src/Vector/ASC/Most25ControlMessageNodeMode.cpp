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

#include <Vector/ASC/Most25ControlMessageNodeMode.h>
#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

Most25ControlMessageNodeMode * Most25ControlMessageNodeMode::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS REGEX_MOST_Dir
                     REGEX_WS REGEX_MOST_SourceAdr REGEX_WS REGEX_MOST_DestAdr REGEX_WS REGEX_MOST_RType
                     "((" REGEX_WS REGEX_MOST_Dx"){17})"
                     REGEX_WS REGEX_MOST_State2 REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * most25ControlMessageNodeMode = new Most25ControlMessageNodeMode;
        most25ControlMessageNodeMode->time = std::stod(match[1]);
        most25ControlMessageNodeMode->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
            most25ControlMessageNodeMode->dir = Dir::Rx;
        else if (match[3] == "Tx")
            most25ControlMessageNodeMode->dir = Dir::Tx;
        most25ControlMessageNodeMode->sourceAdr = std::stoul(match[4], nullptr, file.base);
        most25ControlMessageNodeMode->destAdr = std::stoul(match[5], nullptr, file.base);
        most25ControlMessageNodeMode->rType = std::stoul(match[6], nullptr, file.base);
        std::istringstream iss(match[7]);
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
            most25ControlMessageNodeMode->data.push_back(s);
        }
        most25ControlMessageNodeMode->state2 = std::stoul(match[9], nullptr, file.base);
        return most25ControlMessageNodeMode;
    }

    return nullptr;
}

void Most25ControlMessageNodeMode::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);
    writeMostDir(file, stream, dir);
    writeMostSourceAdr(file, stream, sourceAdr);
    writeMostDestAdr(file, stream, destAdr);
    writeMostRType(file, stream, rType);
    stream << ' ';
    writeMostData(file, stream, data);
    stream << ' ';
    writeMostState2(file, stream, state2);

    stream << endl;
}

}
}
