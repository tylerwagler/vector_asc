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
#include "FlexRayError.h"
#include "FlexRaySymbolsRegEx.h"

namespace Vector {
namespace ASC {

FlexRayError::FlexRayError() :
    Event(),
    time(0.0),
    clusterNr(0),
    clientId(0),
    channelNr(0),
    channelMask(0),
    ccType(0),
    ccData()
{
    eventType = EventType::FlexRayError;
}

FlexRayError::~FlexRayError()
{
}

FlexRayError * FlexRayError::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "EE"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayError * flexRayError = new FlexRayError;
        flexRayError->time = std::stod(match[1]);
        flexRayError->clusterNr = std::stoul(match[2]);
        flexRayError->clientId = std::stoul(match[3]);
        flexRayError->channelNr = std::stoul(match[4]);
        flexRayError->channelMask = std::stoul(match[5]);
        flexRayError->ccType = std::stoul(match[6]);
        flexRayError->ccData[0] = std::stoul(match[7]);
        flexRayError->ccData[1] = std::stoul(match[8]);
        flexRayError->ccData[2] = std::stoul(match[9]);
        flexRayError->ccData[3] = std::stoul(match[10]);
        return flexRayError;
    }

    return nullptr;
}

void FlexRayError::write(File & file, std::ostream & stream)
{
    stream << endl;
}

}
}
