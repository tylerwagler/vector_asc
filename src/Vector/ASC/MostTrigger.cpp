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
#include <Vector/ASC/MostTrigger.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostTrigger * MostTrigger::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "Trigger:"
                     REGEX_ws REGEX_MOST_TrigMode REGEX_WS REGEX_MOST_TrigHW REGEX_WS REGEX_MOST_TrigValue
                     REGEX_WS REGEX_MOST_TrigValue REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostTrigger = new MostTrigger;
        mostTrigger->time = std::stod(match[1]);
        mostTrigger->channel = std::stoul(match[2]);
        switch (std::stoul(match[3], nullptr, 16)) {
        case 0:
            mostTrigger->trigMode = MostTrigMode::Unknown;
            break;
        case 1:
            mostTrigger->trigMode = MostTrigMode::SynchronizationMaster;
            break;
        case 2:
            mostTrigger->trigMode = MostTrigMode::SynchronizationSlave;
            break;
        }
        mostTrigger->trigHw = std::stoul(match[4], nullptr, 16);
        mostTrigger->trigValue[0] = std::stoul(match[5], nullptr, 16);
        mostTrigger->trigValue[1] = std::stoul(match[6], nullptr, 16);
        return mostTrigger;
    }

    return nullptr;
}

void MostTrigger::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "Trigger:  %1X %1X %08X %08X" */
    stream
            << "Trigger:  "
            << std::setw(1) << std::uppercase << std::hex << (uint16_t) trigMode
            << ' ' << std::setw(1) << std::uppercase << std::hex << (uint16_t) trigHw
            << ' ' << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << trigValue[0]
            << ' ' << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << trigValue[1];

    stream << endl;
}

}
}
