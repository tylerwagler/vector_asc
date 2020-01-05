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
#include <Vector/ASC/MostEcl.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostEcl * MostEcl::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "Ecl:"
                     REGEX_ws REGEX_MOST_EclMode REGEX_WS REGEX_MOST_EclState REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostEcl = new MostEcl;
        mostEcl->time = std::stod(match[1]);
        mostEcl->channel = std::stoul(match[2]);
        switch (std::stoul(match[3])) {
        case 0:
            mostEcl->eclMode = MostEclMode::Discrete;
            switch (std::stoul(match[4])) {
            case 0:
                mostEcl->eclState = MostEclState::LineLow;
                break;
            case 1:
                mostEcl->eclState = MostEclState::LineHigh;
                break;
            }
            break;
        case 1:
            mostEcl->eclMode = MostEclMode::Sequence;
            switch (std::stoul(match[4])) {
            case 0:
                mostEcl->eclState = MostEclState::SequenceStopped;
                break;
            case 1:
                mostEcl->eclState = MostEclState::SequenceStarted;
                break;
            }
            break;
        }
        return mostEcl;
    }

    return nullptr;
}

void MostEcl::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "Ecl:      %1X %1X" */
    stream
            << "Ecl:      "
            << std::setw(1) << std::uppercase << std::hex << (uint16_t) eclMode
            << ' '
            << std::setw(1) << std::uppercase << std::hex << (uint16_t) eclState;

    stream << endl;
}

}
}
