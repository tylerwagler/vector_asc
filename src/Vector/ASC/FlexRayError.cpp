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
#include <Vector/ASC/FlexRayError.h>
#include <Vector/ASC/FlexRaySymbolsRegEx.h>

namespace Vector {
namespace ASC {

FlexRayError * FlexRayError::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "EE"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * flexRayError = new FlexRayError;
        flexRayError->time = std::stod(match[1]);
        flexRayError->clusterNr = std::stoul(match[2]);
        flexRayError->clientId = std::stoul(match[3]);
        flexRayError->channelNr = std::stoul(match[4]);
        flexRayError->channelMask = std::stoul(match[5]);
        flexRayError->ccType = std::stoul(match[6], nullptr, file.base);
        flexRayError->ccData[0] = std::stoul(match[7], nullptr, file.base);
        flexRayError->ccData[1] = std::stoul(match[8], nullptr, file.base);
        flexRayError->ccData[2] = std::stoul(match[9], nullptr, file.base);
        flexRayError->ccData[3] = std::stoul(match[10], nullptr, file.base);
        return flexRayError;
    }

    return nullptr;
}

void FlexRayError::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << " Fr ";

    /* format: "EE " */
    stream << "EE ";

    stream
            << std::dec
            << clusterNr
            << ' ' << clientId
            << ' ' << channelNr
            << ' ' << channelMask;

    switch (file.base) {
    case 10:
        stream
                << ' ' << std::dec << ccType
                << ' ' << std::dec << ccData[0]
                << ' ' << std::dec << ccData[1]
                << ' ' << std::dec << ccData[2]
                << ' ' << std::dec << ccData[3];
        break;
    case 16:
        stream
                << ' ' << std::hex << ccType
                << ' ' << std::hex << ccData[0]
                << ' ' << std::hex << ccData[1]
                << ' ' << std::hex << ccData[2]
                << ' ' << std::hex << ccData[3];
        break;
    }

    stream << endl;
}

}
}
