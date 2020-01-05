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

#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostNetState.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostNetState * MostNetState::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "NetState:"
                     REGEX_ws REGEX_MOST_NetStateOld REGEX_WS REGEX_MOST_NetStateNew REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostNetState = new MostNetState;
        mostNetState->time = std::stod(match[1]);
        mostNetState->channel = std::stoul(match[2]);
        mostNetState->netStateOld = std::stoul(match[3]);
        mostNetState->netStateNew = std::stoul(match[4]);
        return mostNetState;
    }

    return nullptr;
}

void MostNetState::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "NetState: %1X %1X" */
    stream
            << "NetState: "
            << std::setw(1) << std::uppercase << std::hex << (uint16_t) netStateOld
            << ' '
            << std::setw(1) << std::uppercase << std::hex << (uint16_t) netStateNew;

    stream << endl;
}

}
}
