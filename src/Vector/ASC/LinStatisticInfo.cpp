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

#include <regex>
#include "LinStatisticInfo.h"

namespace Vector {
namespace ASC {

LinStatisticInfo::LinStatisticInfo() :
    Event(),
    time(0.0),
    channel(),
    channelNum(0),
    busLoad(0.0),
    burstsTotal(0),
    burstsOverrun(0),
    framesSent(0),
    framesReceived(0),
    framesUnanswered(0)
{
    eventType = EventType::LinStatisticInfo;
}

LinStatisticInfo::~LinStatisticInfo()
{
}

LinStatisticInfo * LinStatisticInfo::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " Statistic"
                " ([[:digit:]]+)"
                " ([[:digit:].]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinStatisticInfo * linStatisticInfo = new LinStatisticInfo;
        linStatisticInfo->time = std::stof(match[1]);
        linStatisticInfo->channel = match[2];
        linStatisticInfo->channelNum = std::stoul(match[3]);
        linStatisticInfo->busLoad = std::stof(match[4]);
        linStatisticInfo->burstsTotal = std::stoul(match[5]);
        linStatisticInfo->burstsOverrun = std::stoul(match[6]);
        linStatisticInfo->framesSent = std::stoul(match[7]);
        linStatisticInfo->framesReceived = std::stoul(match[8]);
        linStatisticInfo->framesUnanswered = std::stoul(match[9]);
        return linStatisticInfo;
    }

    return nullptr;
}

void LinStatisticInfo::write(File & file, std::ostream & stream)
{
}

}
}
