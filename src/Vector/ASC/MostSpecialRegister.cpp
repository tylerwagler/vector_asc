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

#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostSpecialRegister.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostSpecialRegister * MostSpecialRegister::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "Register:"
                     REGEX_ws REGEX_MOST_RegSubType REGEX_WS REGEX_MOST_RegID REGEX_WS REGEX_MOST_RegValue REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostSpecialRegister = new MostSpecialRegister;
        mostSpecialRegister->time = std::stod(match[1]);
        mostSpecialRegister->channel = std::stoul(match[2]);
        switch (std::stoul(match[3])) {
        case 0:
            mostSpecialRegister->regSubType = MostRegSubType::Unspecified;
            break;
        case 1:
            mostSpecialRegister->regSubType = MostRegSubType::Notify;
            break;
        case 2:
            mostSpecialRegister->regSubType = MostRegSubType::ReadRequest;
            break;
        case 3:
            mostSpecialRegister->regSubType = MostRegSubType::WriteRequest;
            break;
        case 4:
            mostSpecialRegister->regSubType = MostRegSubType::ReadResult;
            break;
        case 5:
            mostSpecialRegister->regSubType = MostRegSubType::WriteResult;
            break;
        case 6:
            mostSpecialRegister->regSubType = MostRegSubType::ReadFailed;
            break;
        case 7:
            mostSpecialRegister->regSubType = MostRegSubType::WriteFailed;
            break;
        }
        mostSpecialRegister->regId = std::stoul(match[4], nullptr, 16);
        mostSpecialRegister->regValue = std::stoul(match[5], nullptr, 16);
        return mostSpecialRegister;
    }

    return nullptr;
}

void MostSpecialRegister::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "Register: %1X %02X %012I64X" */
    /* format: "Register: %1X %02X %04I64X" */
    stream
            << "Register: "
            << std::setw(1) << std::uppercase << std::hex << (uint16_t) regSubType
            << ' '
            << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) regId
            << ' '
            << std::setfill('0') << std::setw(4 /* @todo 4 or 12 */) << std::uppercase << std::hex << regValue;

    stream << endl;
}

}
}
