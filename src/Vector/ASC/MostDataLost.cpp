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
#include <Vector/ASC/MostDataLost.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostDataLost * MostDataLost::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "DataLost:"
                     REGEX_ws REGEX_MOST_DLInfo REGEX_WS REGEX_MOST_DLCtrl REGEX_WS REGEX_MOST_DLAsync
                     REGEX_WS REGEX_MOST_DLTime REGEX_WS REGEX_MOST_DLTime REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostDataLost = new MostDataLost;
        mostDataLost->time = std::stod(match[1]);
        mostDataLost->channel = std::stoul(match[2]);
        mostDataLost->dlInfo = std::stoul(match[3], nullptr, 16);
        mostDataLost->dlCtrl = std::stoul(match[4], nullptr, file.base);
        mostDataLost->dlAsync = std::stoul(match[5], nullptr, file.base);
        mostDataLost->dlTime[0] = std::stod(match[6]);
        mostDataLost->dlTime[1] = std::stod(match[7]);
        return mostDataLost;
    }

    return nullptr;
}

void MostDataLost::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "DataLost: %08X %5d %5d %s %s" */
    /* format: "DataLost: %08X %04X %04X %s %s" */
    stream
            << "DataLost: "
            << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << dlInfo
            << ' ';
    switch (file.base) {
    case 10:
        stream
                << std::setfill(' ') << std::setw(5) << std::dec << dlCtrl
                << ' ' << std::setfill(' ') << std::setw(5) << std::dec << dlAsync;
        break;
    case 16:
        stream
                << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << dlCtrl
                << ' ' << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << dlAsync;
        break;
    }
    stream
            << ' ' << std::setprecision(5) << std::fixed << dlTime[0]
            << ' ' << std::setprecision(5) << std::fixed << dlTime[1];

    stream << endl;
}

}
}
