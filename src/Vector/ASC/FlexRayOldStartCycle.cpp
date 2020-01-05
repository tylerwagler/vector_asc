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
#include <Vector/ASC/FlexRayOldStartCycle.h>
#include <Vector/ASC/FlexRaySymbolsRegEx.h>

namespace Vector {
namespace ASC {

FlexRayOldStartCycle * FlexRayOldStartCycle::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_FlexRayOld_Time REGEX_WS REGEX_FlexRayOld_Channel REGEX_WS "StartCycleEvent"
                     REGEX_WS "NM Vector:" REGEX_ws REGEX_FlexRayOld_DLC "((" REGEX_WS REGEX_FlexRayOld_Dx "){0,255})" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * flexRayOldStartCycle = new FlexRayOldStartCycle;
        flexRayOldStartCycle->time = std::stod(match[1]);
        flexRayOldStartCycle->channel = std::string(match[2])[0];
        flexRayOldStartCycle->dlc = std::stoul(match[3]);
        std::istringstream iss(match[4]);
        iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            flexRayOldStartCycle->data.push_back(s);
        }
        return flexRayOldStartCycle;
    }

    return nullptr;
}

void FlexRayOldStartCycle::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream
            << " Fr "
            << channel
            << " StartCycleEvent NM Vector: "
            << std::dec << (uint16_t) dlc;
    for (FlexRayOldDx d : data)
        stream << ' ' << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) d;

    stream << endl;
}

}
}
