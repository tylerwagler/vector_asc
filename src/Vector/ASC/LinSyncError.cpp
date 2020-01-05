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

#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinSyncError.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinSyncError * LinSyncError::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS "SyncError"
                     "((" REGEX_WS REGEX_LIN_TimeInterval "){4})"
                     "(" REGEX_WS "SOF" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame
                     REGEX_WS "BR" REGEX_ws "=" REGEX_ws REGEX_LIN_baudrate
                     REGEX_WS "break" REGEX_ws "=" REGEX_ws REGEX_LIN_SyncBreak REGEX_WS REGEX_LIN_SyncDel ")?"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linSyncError = new LinSyncError;
        linSyncError->time = std::stod(match[1]);
        linSyncError->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        std::istringstream iss(match[3]);
        for (int i = 0; i < 4; ++i) {
            unsigned short s;
            iss >> s;
            linSyncError->timeInterval[i] = s;
        }
        if (match[5] != "") {
            linSyncError->startOfFrame = std::stod(match[6]);
            linSyncError->baudrate = std::stoul(match[7]);
            linSyncError->syncBreak = std::stoul(match[8]);
            linSyncError->syncDel = std::stoul(match[9]);
        }
        return linSyncError;
    }

    return nullptr;
}

void LinSyncError::write(File & file, std::ostream & stream) {
    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s              SyncError " */
    writeLinChannel(file, stream, channel);
    stream << "              SyncError ";

    for (LinTimeInterval ti : timeInterval)
        stream << ' ' << std::setw(3) << std::dec << ti;
    if (file.version >= File::Version::Ver_6_1) {
        writeLinStartOfFrame(file, stream, startOfFrame);
        writeLinBaudrate(file, stream, baudrate);
        writeLinSyncBreak(file, stream, syncBreak);
        writeLinSyncDel(file, stream, syncDel);
    }

    stream << endl;
}

}
}
