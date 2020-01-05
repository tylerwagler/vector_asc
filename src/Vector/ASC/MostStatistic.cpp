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
#include <Vector/ASC/MostStatistic.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

MostStatistic * MostStatistic::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "MostStatistic:"
                     REGEX_ws "Fr:" REGEX_ws REGEX_MOST_StatVal
                     REGEX_WS "Lt:" REGEX_ws REGEX_MOST_StatVal
                     REGEX_WS "Bl:" REGEX_ws REGEX_MOST_StatVal
                     REGEX_WS "Pk:" REGEX_ws REGEX_MOST_StatVal REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * mostStatistic = new MostStatistic;
        mostStatistic->time = std::stod(match[1]);
        mostStatistic->channel = std::stoul(match[2]);
        mostStatistic->fr = std::stoul(match[3]);
        mostStatistic->lt = std::stoul(match[4]);
        mostStatistic->bl = std::stoul(match[5]);
        mostStatistic->pk = std::stoul(match[6]);
        return mostStatistic;
    }

    return nullptr;
}

void MostStatistic::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "MostStatistic:  Fr: %5u Lt: %5u Bl: %5u Pk: %5u" */
    stream
            << "MostStatistic:  Fr: "
            << std::setw(5) << std::dec << fr
            << " Lt: "
            << std::setw(5) << std::dec << lt
            << " Bl: "
            << std::setw(5) << std::dec << bl
            << " Pk: "
            << std::setw(5) << std::dec << pk;

    stream << endl;
}

}
}
