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

#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinSpike.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinSpike * LinSpike::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS "Spike"
                     REGEX_WS REGEX_LIN_Dir REGEX_WS REGEX_LIN_SpikeLength REGEX_WS "microseconds"
                     "(" REGEX_WS "SOF" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame
                     REGEX_WS "BR" REGEX_ws "=" REGEX_ws REGEX_LIN_baudrate REGEX_ws ")?" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linSpike = new LinSpike;
        linSpike->time = std::stod(match[1]);
        linSpike->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        if (match[3] == "Rx")
            linSpike->dir = Dir::Rx;
        else if (match[3] == "Tx")
            linSpike->dir = Dir::Tx;
        linSpike->spikeLength = std::stoul(match[4]);
        if (match[5] != "") {
            linSpike->startOfFrame = std::stod(match[6]);
            linSpike->baudrate = std::stoul(match[7]);
        }
        return linSpike;
    }

    return nullptr;
}

void LinSpike::write(File & file, std::ostream & stream) {
    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s Spike  %s  %6d microseconds" */
    writeLinChannel(file, stream, channel);
    stream << " Spike  ";
    writeLinDir(file, stream, dir);
    stream
            << "  "
            << std::setw(6) << std::dec << spikeLength
            << " microseconds";

    if (file.version >= File::Version::Ver_6_1) {
        writeLinStartOfFrame(file, stream, startOfFrame);
        writeLinBaudrate(file, stream, baudrate);
    }

    stream << endl;
}

}
}
