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

#include <Vector/ASC/CanCommon.h>
#include <Vector/ASC/CanFdExtendedMessage.h>
#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

CanFdExtendedMessage * CanFdExtendedMessage::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "CANFD" REGEX_WS REGEX_Channel REGEX_WS REGEX_Dir REGEX_WS REGEX_ID "x"
                     "(" REGEX_WS "([[:alnum:]_]+))?"
                     REGEX_WS REGEX_BRS REGEX_WS REGEX_ESI REGEX_WS REGEX_DLC REGEX_WS REGEX_DataLength
                     "((" REGEX_WS REGEX_Dx "){0,64})"
                     REGEX_WS REGEX_MessageDuration REGEX_WS REGEX_MessageLength
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS REGEX_BitTimingConfArb REGEX_WS REGEX_BitTimingConfData
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * canFdExtendedMessage = new CanFdExtendedMessage;
        canFdExtendedMessage->time = std::stod(match[1]);
        canFdExtendedMessage->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
            canFdExtendedMessage->dir = Dir::Rx;
        else if (match[3] == "Tx")
            canFdExtendedMessage->dir = Dir::Tx;
        canFdExtendedMessage->id = std::stoul(match[4], nullptr, 16);
        if (match[5] != "")
            canFdExtendedMessage->symbolicName = match[6];
        canFdExtendedMessage->brs = (match[7] == '1');
        canFdExtendedMessage->esi = (match[8] == '1');
        canFdExtendedMessage->dlc = std::stoul(match[9], nullptr, 16);
        canFdExtendedMessage->dataLength = std::stoul(match[10]);
        std::istringstream iss(match[11]);
        iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            canFdExtendedMessage->data.push_back(s);
        }
        canFdExtendedMessage->messageDuration = std::stoul(match[13]);
        canFdExtendedMessage->messageLength = std::stoul(match[14]);
        canFdExtendedMessage->flags = std::stoul(match[15]);
        canFdExtendedMessage->crc = std::stoul(match[16], nullptr, 16);
        canFdExtendedMessage->bitTimingConfArb = std::stoul(match[17], nullptr, 16);
        canFdExtendedMessage->bitTimingConfData = std::stoul(match[18], nullptr, 16);
        return canFdExtendedMessage;
    }

    return nullptr;
}

void CanFdExtendedMessage::write(File & file, std::ostream & stream) {
    if (file.version < File::Version::Ver_8_1)
        return;

    writeTime(file, stream, time);
    stream << ' ';

    /* format: "CANFD  " */
    stream << "CANFD  ";

    stream << ' ' << std::dec << (uint16_t) channel << "  ";
    writeDir(file, stream, dir);
    stream << ' ';
    std::stringstream ss;
    switch (file.base) {
    case 10:
        ss << std::dec << id << 'x';
        stream << std::left << std::setfill(' ') << std::setw(15) << ss.str();
        break;
    case 16:
        ss << std::hex << id << 'x';
        stream << std::left << std::setfill(' ') << std::setw(15) << ss.str();
        break;
    }
    stream
            << ' ' << symbolicName
            << ' ' << (brs ? '1' : '0')
            << ' ' << (esi ? '1' : '0')
            << ' ';
    switch (file.base) {
    case 10:
        stream << std::dec << (uint16_t) dlc;
        break;
    case 16:
        stream << std::hex << (uint16_t) dlc;
        break;
    }
    stream << ' ' << std::dec << (uint16_t) dataLength;
    writeData(file, stream, data);
    stream
            << ' ' << std::setfill(' ') << std::setw(8) << std::dec << messageDuration
            << ' ' << std::setfill(' ') << std::setw(4) << std::dec << messageLength
            << ' ' << std::setfill(' ') << std::setw(8) << std::dec << flags
            << ' ' << std::setfill(' ') << std::setw(8) << std::hex << crc
            << ' ' << std::setfill('0') << std::setw(8) << std::hex << bitTimingConfArb
            << ' ' << std::setfill('0') << std::setw(8) << std::hex << bitTimingConfData;

    stream << endl;
}

}
}
