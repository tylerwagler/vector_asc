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

#include <Vector/ASC/FlexRayCommon.h>
#include <Vector/ASC/FlexRayOldMessage.h>
#include <Vector/ASC/FlexRaySymbolsRegEx.h>

namespace Vector {
namespace ASC {

FlexRayOldMessage * FlexRayOldMessage::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_FlexRayOld_Time REGEX_WS REGEX_FlexRayOld_Channel REGEX_WS "V9"
                     REGEX_WS REGEX_FlexRayOld_ID REGEX_WS REGEX_FlexRayOld_Cycle REGEX_WS REGEX_FlexRayOld_NM
                     REGEX_WS REGEX_FlexRayOld_Sync REGEX_WS REGEX_FlexRayOld_HeaderCRC
                     REGEX_WS REGEX_FlexRayOld_SymbolicName REGEX_WS REGEX_FlexRayOld_DLC
                     "((" REGEX_WS REGEX_FlexRayOld_Dx "){0,255})" REGEX_WS REGEX_FlexRayOld_FrameState
                     REGEX_WS REGEX_FlexRayOld_HeaderBitMask REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * flexRayOldMessage = new FlexRayOldMessage;
        flexRayOldMessage->time = std::stod(match[1]);
        flexRayOldMessage->channel = std::string(match[2])[0];
        flexRayOldMessage->id = std::stoul(match[3]);
        flexRayOldMessage->cycle = std::stoul(match[4]);
        flexRayOldMessage->nm = (match[5] == '1');
        flexRayOldMessage->sync = (match[6] == '1');
        flexRayOldMessage->headerCrc = std::stoul(match[7]);
        flexRayOldMessage->symbolicName = match[8];
        flexRayOldMessage->dlc = std::stoul(match[9]);
        std::istringstream iss(match[10]);
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            flexRayOldMessage->data.push_back(s);
        }
        flexRayOldMessage->frameState = std::stoul(match[12], nullptr, 16);
        flexRayOldMessage->headerBitMask = std::stoul(match[13], nullptr, 16);
        return flexRayOldMessage;
    }

    return nullptr;
}

void FlexRayOldMessage::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream
            << " Fr "
            << channel
            << " V9  "
            << std::dec << id
            << ' ' << (uint16_t) cycle
            << ' ' << (nm ? '1' : '0')
            << ' ' << (sync ? '1' : '0')
            << ' ' << headerCrc
            << ' ' << symbolicName
            << ' ' << std::setfill(' ') << std::setw(2) << std::dec << (uint16_t) dlc;
    for (FlexRayOldDx d : data)
        stream << ' ' << std::setfill(' ') << std::setw(3) << std::dec << (uint16_t) d;
    stream
            << ' ' << std::setfill('0') << std::setw(4) << std::hex << frameState
            << ' ' << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) headerBitMask;

    stream << endl;
}

}
}
