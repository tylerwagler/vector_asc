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

#include <Vector/ASC/CanBusStatistics.h>
#include <Vector/ASC/CanCommon.h>
#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

CanBusStatistics * CanBusStatistics::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS REGEX_Channel REGEX_WS "Statistic:"
                     REGEX_WS "D" REGEX_WS REGEX_StatNumber
                     REGEX_WS "R" REGEX_WS REGEX_StatNumber
                     REGEX_WS "XD" REGEX_WS REGEX_StatNumber
                     REGEX_WS "XR" REGEX_WS REGEX_StatNumber
                     REGEX_WS "E" REGEX_WS REGEX_StatNumber
                     REGEX_WS "O" REGEX_WS REGEX_StatNumber
                     REGEX_WS "B" REGEX_WS REGEX_StatPercent "%"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * canBusStatistics = new CanBusStatistics;
        canBusStatistics->time = std::stod(match[1]);
        canBusStatistics->channel = std::stoul(match[2]);
        canBusStatistics->dataFrames = std::stoul(match[3]);
        canBusStatistics->remoteFrames = std::stoul(match[4]);
        canBusStatistics->extendedDataFrames = std::stoul(match[5]);
        canBusStatistics->extendedRemoteFrames = std::stoul(match[6]);
        canBusStatistics->errorFrames = std::stoul(match[7]);
        canBusStatistics->overloadFrames = std::stoul(match[8]);
        canBusStatistics->busload = std::stod(match[9]);
        return canBusStatistics;
    }

    return nullptr;
}

void CanBusStatistics::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << ' ' << std::dec << (uint16_t) channel << "  ";

    /* format: "Statistic: D %lu R %lu XD %lu XR %lu E %lu O %lu B %u.%d%%" */
    stream
            << "Statistic:"
            << " D " << std::dec << dataFrames
            << " R " << std::dec << remoteFrames
            << " XD " << std::dec << extendedDataFrames
            << " XR " << std::dec << extendedRemoteFrames
            << " E " << std::dec << errorFrames
            << " O " << std::dec << overloadFrames
            << " B " << std::fixed << std::setprecision(1) << busload << '%';

    stream << endl;
}

}
}
