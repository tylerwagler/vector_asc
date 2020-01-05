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
#include <Vector/ASC/LinSlaveTimeout.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinSlaveTimeout * LinSlaveTimeout::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS "SlaveTimeout"
                     REGEX_WS "slave-id" REGEX_ws "=" REGEX_ws REGEX_LIN_slaveId ","
                     REGEX_ws "current state" REGEX_ws "=" REGEX_ws REGEX_LIN_state ","
                     REGEX_ws "following state" REGEX_ws "=" REGEX_ws REGEX_LIN_state REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linSlaveTimeout = new LinSlaveTimeout;
        linSlaveTimeout->time = std::stod(match[1]);
        linSlaveTimeout->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linSlaveTimeout->slaveId = std::stoul(match[3]);
        linSlaveTimeout->currentState = std::stoul(match[4]);
        linSlaveTimeout->followingState = std::stoul(match[5]);
        return linSlaveTimeout;
    }

    return nullptr;
}

void LinSlaveTimeout::write(File & file, std::ostream & stream) {
    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s SlaveTimeout  slave-id = %d, current state = %d, following state = %d" */
    writeLinChannel(file, stream, channel);
    stream
            << " SlaveTimeout  slave-id = "
            << std::dec << (uint16_t) slaveId
            << ", current state = "
            << std::dec << (uint16_t) currentState
            << ", following state = "
            << std::dec << (uint16_t) followingState;

    stream << endl;
}

}
}
