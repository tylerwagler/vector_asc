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
#include <Vector/ASC/CanExtendedMessage.h>
#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

CanExtendedMessage * CanExtendedMessage::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS REGEX_Channel REGEX_WS REGEX_ID "x" REGEX_WS REGEX_Dir REGEX_WS "d" REGEX_WS REGEX_DLC
                     "((" REGEX_WS REGEX_Dx "){0,8})"
                     "(" REGEX_WS "Length" REGEX_ws "=" REGEX_ws REGEX_MessageDuration ")?"
                     "(" REGEX_WS "BitCount" REGEX_ws "=" REGEX_ws REGEX_MessageLength ")?"
                     "(" REGEX_WS REGEX_MessageFlags ")?"
                     "(" REGEX_WS "ID" REGEX_ws "=" REGEX_ws REGEX_IDnum "x)?"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * canExtendedMessage = new CanExtendedMessage;
        canExtendedMessage->time = std::stod(match[1]);
        canExtendedMessage->channel = std::stoul(match[2]);
        canExtendedMessage->id = std::stoul(match[3], nullptr, file.base);
        if (match[4] == "Rx")
            canExtendedMessage->dir = Dir::Rx;
        else if (match[4] == "Tx")
            canExtendedMessage->dir = Dir::Tx;
        canExtendedMessage->dlc = std::stoul(match[5], nullptr, file.base);
        std::istringstream iss(match[6]);
        if (file.base == 10)
            iss >> std::dec;
        if (file.base == 16)
            iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            canExtendedMessage->data.push_back(s);
        }
        if (match[8] != "")
            canExtendedMessage->messageDuration = std::stoul(match[9]);
        if (match[10] != "")
            canExtendedMessage->messageLength = std::stoul(match[11]);
        if (match[12] != "") {
            if (match[13] == " TE")
                canExtendedMessage->messageFlags.te = true;
            else if (match[13] == " WU")
                canExtendedMessage->messageFlags.wu = true;
            else if (match[13] == " XX") {
                canExtendedMessage->messageFlags.te = true;
                canExtendedMessage->messageFlags.wu = true;
            }
        }
        if (match[14] != "")
            canExtendedMessage->messageId = std::stoul(match[15]);
        return canExtendedMessage;
    }

    return nullptr;
}

void CanExtendedMessage::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << ' ' << std::dec << (uint16_t) channel << "  ";
    std::stringstream ss;
    switch (file.base) {
    case 10:
        ss << std::dec << id << 'x';
        stream << std::left << std::setfill(' ') << std::setw(15) << ss.str();
        break;
    case 16:
        ss << std::uppercase << std::hex << id << 'x';
        stream << std::left << std::setfill(' ') << std::setw(15) << ss.str();
        break;
    }
    stream << ' ';
    writeDir(file, stream, dir);
    stream
            << " d " << std::hex << (uint16_t) dlc
            << std::uppercase;
    writeData(file, stream, data);

    if (file.version >= File::Version::Ver_7_5) {
        /* format: " Length= " */
        stream << " Length = ";

        stream << std::dec << messageDuration;

        /* format: " BitCount = " */
        stream << " BitCount = ";

        stream << std::dec << messageLength;
    }

#if 0
    /* <MessageFlags> */
    if (!messageFlags.empty())
        stream << ' ' << std::dec << messageFlags;
#endif

    if (file.version >= File::Version::Ver_8_0) {
        /* format: " ID = " */
        stream << " ID = ";

        stream << std::dec << messageId;
        stream << 'x';
    }

    stream << endl;
}

}
}
