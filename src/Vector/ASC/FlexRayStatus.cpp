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

#include <Vector/ASC/FlexRayCommon.h>
#include <Vector/ASC/FlexRayStatus.h>
#include <Vector/ASC/FlexRaySymbolsRegEx.h>

namespace Vector {
namespace ASC {

FlexRayStatus * FlexRayStatus::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "SE"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([012])"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([01234])" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([01])" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * flexRayStatus = new FlexRayStatus;
        flexRayStatus->time = std::stod(match[1]);
        flexRayStatus->clusterNr = std::stoul(match[2]);
        flexRayStatus->clientId = std::stoul(match[3]);
        flexRayStatus->channelNr = std::stoul(match[4]);
        flexRayStatus->channelMask = std::stoul(match[5]);
        flexRayStatus->cycleNo = std::stoul(match[6], nullptr, file.base);
        flexRayStatus->ccType = std::stoul(match[7]);
        flexRayStatus->syncState = std::stoul(match[8]);
        flexRayStatus->ccData[0] = std::stoul(match[9], nullptr, file.base);
        flexRayStatus->ccData[1] = std::stoul(match[10], nullptr, file.base);
        flexRayStatus->symbol = std::stoul(match[11]);
        flexRayStatus->wakeUpState = std::stoul(match[12]);
        flexRayStatus->spyFlag = (match[13] == '1');
        return flexRayStatus;
    }

    return nullptr;
}

void FlexRayStatus::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << " Fr ";

    /* format: "SE " */
    stream << "SE ";

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
                << ' ' << std::dec << ccType
                << ' ' << std::dec << syncState
                << ' ' << std::dec << ccData[0]
                << ' ' << std::dec << ccData[1]
                << ' ' << std::dec << symbol
                << ' ' << std::dec << wakeUpState
                << ' ' << (spyFlag ? '1' : '0');
        break;
    case 16:
        stream
                << ' ' << std::hex << cycleNo
                << ' ' << std::dec << ccType
                << ' ' << std::dec << syncState
                << ' ' << std::hex << ccData[0]
                << ' ' << std::hex << ccData[1]
                << ' ' << std::dec << symbol
                << ' ' << std::dec << wakeUpState
                << ' ' << (spyFlag ? '1' : '0');
        break;
    }

    stream << endl;
}

}
}
