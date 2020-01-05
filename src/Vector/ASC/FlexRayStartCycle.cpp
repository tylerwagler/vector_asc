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
#include <Vector/ASC/FlexRayStartCycle.h>
#include <Vector/ASC/FlexRaySymbolsRegEx.h>

namespace Vector {
namespace ASC {

FlexRayStartCycle * FlexRayStartCycle::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "SCE"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS REGEX_FlexRay_Dir
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "NM_Vector:" REGEX_ws "([[:xdigit:]]+)"
                     "(" REGEX_WS "[[:xdigit:]]+){0,12}" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * flexRayStartCycle = new FlexRayStartCycle;
        flexRayStartCycle->time = std::stod(match[1]);
        flexRayStartCycle->clusterNr = std::stoul(match[2]);
        flexRayStartCycle->clientId = std::stoul(match[3]);
        flexRayStartCycle->channelNr = std::stoul(match[4]);
        flexRayStartCycle->channelMask = std::stoul(match[5]);
        flexRayStartCycle->cycleNo = std::stoul(match[6], nullptr, file.base);
        if (match[7] == "Rx")
            flexRayStartCycle->direction = Dir::Rx;
        else if (match[7] == "Tx")
            flexRayStartCycle->direction = Dir::Tx;
        else if (match[7] == "TxRq")
            flexRayStartCycle->direction = Dir::TxRq;
        flexRayStartCycle->ccType = std::stoul(match[8], nullptr, file.base);
        flexRayStartCycle->ccData[0] = std::stoul(match[9], nullptr, file.base);
        flexRayStartCycle->ccData[1] = std::stoul(match[10], nullptr, file.base);
        flexRayStartCycle->ccData[2] = std::stoul(match[11], nullptr, file.base);
        flexRayStartCycle->ccData[3] = std::stoul(match[12], nullptr, file.base);
        flexRayStartCycle->ccData[4] = std::stoul(match[13], nullptr, file.base);
        flexRayStartCycle->nmVectL = std::stoul(match[14], nullptr, file.base);
        if (match[15] != "") {
            std::istringstream iss(match[15]);
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
                flexRayStartCycle->nmVect.push_back(s);
            }
        }
        return flexRayStartCycle;
    }

    return nullptr;
}

void FlexRayStartCycle::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << " Fr ";

    /* format: "SCE " */
    stream << "SCE ";

    stream
            << std::dec
            << clusterNr
            << ' ' << clientId
            << ' ' << channelNr
            << ' ' << channelMask;

    switch (file.base) {
    case 10:
        stream
                << ' ' << std::dec << cycleNo
                << ' ';
        writeDir(file, stream, direction);
        stream
                << ' ' << std::dec << ccType
                << ' ' << std::dec << ccData[0]
                << ' ' << std::dec << ccData[1]
                << ' ' << std::dec << ccData[2]
                << ' ' << std::dec << ccData[3]
                << ' ' << std::dec << ccData[4]
                << " NM_Vector: " << std::dec << nmVectL;
        writeData(file, stream, nmVect);
        break;
    case 16:
        stream
                << ' ' << std::hex << cycleNo
                << ' ';
        writeDir(file, stream, direction);
        stream
                << ' ' << std::hex << ccType
                << ' ' << std::hex << ccData[0]
                << ' ' << std::hex << ccData[1]
                << ' ' << std::hex << ccData[2]
                << ' ' << std::hex << ccData[3]
                << ' ' << std::hex << ccData[4]
                << " NM_Vector: " << std::hex << nmVectL;
        writeData(file, stream, nmVect);
        break;
    }

    stream << endl;
}

}
}
