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
#include "FlexRayCommon.h"
#include "FlexRayStartCycle.h"
#include "FlexRaySymbolsRegEx.h"

namespace Vector {
namespace ASC {

FlexRayStartCycle::FlexRayStartCycle() :
    Event(),
    time(0.0),
    clusterNr(0),
    clientId(0),
    channelNr(0),
    channelMask(0),
    cycleNo(0),
    direction(),
    ccType(0),
    ccData(),
    nmVectL(0),
    nmVect()
{
    eventType = EventType::FlexRayStartCycle;
}

FlexRayStartCycle::~FlexRayStartCycle()
{
}

FlexRayStartCycle * FlexRayStartCycle::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "SCE"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS REGEX_FlexRay_Dir
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "NM_Vector:" REGEX_ws "([[:xdigit:]]+)"
                     "(" REGEX_WS "[[:xdigit:]]+){0,12}" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayStartCycle * flexRayStartCycle = new FlexRayStartCycle;
        flexRayStartCycle->time = std::stod(match[1]);
        flexRayStartCycle->clusterNr = std::stoul(match[2]);
        flexRayStartCycle->clientId = std::stoul(match[3]);
        flexRayStartCycle->channelNr = std::stoul(match[4]);
        flexRayStartCycle->channelMask = std::stoul(match[5]);
        flexRayStartCycle->cycleNo = std::stoul(match[6]);
        flexRayStartCycle->direction = match[7];
        flexRayStartCycle->ccType = std::stoul(match[8]);
        flexRayStartCycle->ccData[0] = std::stoul(match[9]);
        flexRayStartCycle->ccData[1] = std::stoul(match[10]);
        flexRayStartCycle->ccData[2] = std::stoul(match[11]);
        flexRayStartCycle->ccData[3] = std::stoul(match[12]);
        flexRayStartCycle->ccData[4] = std::stoul(match[13]);
        flexRayStartCycle->nmVectL = std::stoul(match[14]);
        std::istringstream iss(match[15]);
        for (uint8_t i = 0; i < flexRayStartCycle->nmVectL; ++i) {
            unsigned short s;
            iss >> s;
            flexRayStartCycle->nmVect[i] = s;
        }
        return flexRayStartCycle;
    }

    return nullptr;
}

void FlexRayStartCycle::write(File & file, std::ostream & stream)
{
    stream << endl;
}

}
}
