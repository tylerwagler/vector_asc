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

#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostLightLock.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostLightLock * MostLightLock::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "LL:" REGEX_ws REGEX_MOST_LLState REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostLightLock = new MostLightLock;
        mostLightLock->time = std::stod(match[1]);
        mostLightLock->channel = std::stoul(match[2]);
        mostLightLock->llState = std::stoul(match[3], nullptr, file.base);
        return mostLightLock;
    }

    return nullptr;
}

void MostLightLock::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "LL: %hu" */
    /* format: "LL: %hX" */
    stream << "LL: ";
    switch (file.base) {
    case 10:
        stream << std::dec << (uint16_t) llState;
        break;
    case 16:
        stream << std::uppercase << std::hex << (uint16_t) llState;
        break;
    }

    stream << endl;
}

}
}
