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

#include <Vector/ASC/CanCommon.h>
#include <Vector/ASC/CanSymbolsRegEx.h>
#include <Vector/ASC/GlobalMarker.h>

namespace Vector {
namespace ASC {

GlobalMarker * GlobalMarker::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([01])"
                     REGEX_WS "GMGroup:" REGEX_ws "(.+?)"
                     REGEX_WS "GMMarker:" REGEX_ws "(.+?)"
                     REGEX_WS "GMDescription:" REGEX_ws "(.+?)"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * globalMarker = new GlobalMarker;
        globalMarker->time = std::stod(match[1]);
        globalMarker->type = std::stoul(match[2]);
        globalMarker->backgroundColor = std::stoul(match[3]);
        globalMarker->foregroundColor = std::stoul(match[4]);
        globalMarker->relocatable = (match[5] == '1');
        globalMarker->groupName = match[6];
        globalMarker->markerName = match[7];
        globalMarker->description = match[8];
        return globalMarker;
    }

    return nullptr;
}

void GlobalMarker::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream
            << ' ' << std::dec << type
            << ' ' << backgroundColor
            << ' ' << foregroundColor
            << ' ' << (relocatable ? '1' : '0')
            << " GMGroup: " << groupName
            << " GMMarker: " << markerName
            << " GMDescription: " << description;

    stream << endl;
}

}
}
