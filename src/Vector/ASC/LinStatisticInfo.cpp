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

#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinStatisticInfo.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinStatisticInfo * LinStatisticInfo::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS "Statistic"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:].]+)"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:digit:]]+)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linStatisticInfo = new LinStatisticInfo;
        linStatisticInfo->time = std::stod(match[1]);
        linStatisticInfo->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linStatisticInfo->channelNum = std::stoul(match[3]);
        linStatisticInfo->busLoad = std::stod(match[4]);
        linStatisticInfo->burstsTotal = std::stoul(match[5]);
        linStatisticInfo->burstsOverrun = std::stoul(match[6]);
        linStatisticInfo->framesSent = std::stoul(match[7]);
        linStatisticInfo->framesReceived = std::stoul(match[8]);
        linStatisticInfo->framesUnanswered = std::stoul(match[9]);
        return linStatisticInfo;
    }

    return nullptr;
}

void LinStatisticInfo::write(File & file, std::ostream & stream) {
    if (file.version > File::Version::Ver_5_2)
        return;

    writeLinTime(file, stream, time);
    stream << ' ';
    writeLinChannel(file, stream, channel);

    /* format: "              Statistic" */
    stream << "              Statistic";

    stream << ' ' << std::dec << channelNum;
    stream << ' ' << std::setprecision(6) << std::fixed << busLoad;
    stream << ' ' << std::dec << burstsTotal;
    stream << ' ' << std::dec << burstsOverrun;
    stream << ' ' << std::dec << framesSent;
    stream << ' ' << std::dec << framesReceived;
    stream << ' ' << std::dec << framesUnanswered;

    stream << endl;
}

}
}
