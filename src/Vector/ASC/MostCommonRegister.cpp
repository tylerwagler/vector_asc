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
#include <Vector/ASC/MostCommonRegister.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostCommonRegister * MostCommonRegister::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "RegData:"
                     REGEX_ws REGEX_MOST_RegSubType REGEX_WS REGEX_MOST_RegChip REGEX_WS REGEX_MOST_RegOffset
                     REGEX_WS REGEX_MOST_RegDataLen
                     "((" REGEX_WS REGEX_MOST_Dx ")*)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostCommonRegister = new MostCommonRegister;
        mostCommonRegister->time = std::stod(match[1]);
        mostCommonRegister->channel = std::stoul(match[2]);
        switch (std::stoul(match[3])) {
        case 0:
            mostCommonRegister->regSubType = MostRegSubType::Unspecified;
            break;
        case 1:
            mostCommonRegister->regSubType = MostRegSubType::Notify;
            break;
        case 2:
            mostCommonRegister->regSubType = MostRegSubType::ReadRequest;
            break;
        case 3:
            mostCommonRegister->regSubType = MostRegSubType::WriteRequest;
            break;
        case 4:
            mostCommonRegister->regSubType = MostRegSubType::ReadResult;
            break;
        case 5:
            mostCommonRegister->regSubType = MostRegSubType::WriteResult;
            break;
        case 6:
            mostCommonRegister->regSubType = MostRegSubType::ReadFailed;
            break;
        case 7:
            mostCommonRegister->regSubType = MostRegSubType::WriteFailed;
            break;
        }
        mostCommonRegister->regChip = std::stoul(match[4], nullptr, 16);
        mostCommonRegister->regOffset = std::stoul(match[5], nullptr, 16);
        mostCommonRegister->regDataLen = std::stoul(match[6], nullptr, 16);
        std::istringstream iss(match[7]);
        iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            mostCommonRegister->data.push_back(s);
        }
        return mostCommonRegister;
    }

    return nullptr;
}

void MostCommonRegister::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "RegData:  %1X %02X %04X %02X " */
    stream
            << "RegData:  "
            << std::setw(1) << std::uppercase << std::hex << (uint16_t) regSubType
            << ' '
            << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) regChip
            << ' '
            << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << regOffset
            << ' '
            << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) regDataLen;

    /* format: " %02X" */
    for (MostDx d : data)
        stream << ' ' << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) d;

    stream << endl;
}

}
}
