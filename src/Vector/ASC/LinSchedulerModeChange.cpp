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

#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinSchedulerModeChange.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinSchedulerModeChange * LinSchedulerModeChange::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS "SchedModChng"
                     REGEX_WS "prior scheduler mode" REGEX_ws "=" REGEX_ws REGEX_LIN_scheduleTableIndex ","
                     REGEX_ws "next scheduler mode" REGEX_ws "=" REGEX_ws REGEX_LIN_scheduleTableIndex REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linSchedulerModeChange = new LinSchedulerModeChange;
        linSchedulerModeChange->time = std::stod(match[1]);
        linSchedulerModeChange->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linSchedulerModeChange->priorSchedulerMode = std::stoul(match[3]);
        linSchedulerModeChange->nextSchedulerMode = std::stoul(match[4]);
        return linSchedulerModeChange;
    }

    return nullptr;
}

void LinSchedulerModeChange::write(File & file, std::ostream & stream) {
    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s SchedModChng    prior scheduler mode = %d, next scheduler mode = %d" */
    writeLinChannel(file, stream, channel);
    stream
            << " SchedModChng    prior scheduler mode = "
            << std::dec << (int16_t) priorSchedulerMode
            << ", next scheduler mode = "
            << std::dec << (int16_t) nextSchedulerMode;

    stream << endl;
}

}
}
