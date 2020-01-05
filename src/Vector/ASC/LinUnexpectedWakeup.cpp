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
#include <Vector/ASC/LinUnexpectedWakeup.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinUnexpectedWakeup * LinUnexpectedWakeup::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS "Unexpected wakeup:"
                     "((" REGEX_ws "approx\\." REGEX_ws REGEX_LIN_Width REGEX_ws "us" ")|("
                     REGEX_ws "Signal" REGEX_ws "=" REGEX_ws REGEX_LIN_WakeupByte "))"
                     REGEX_WS "SOF" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame
                     REGEX_WS "BR" REGEX_ws "=" REGEX_ws REGEX_LIN_baudrate REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linUnexpectedWakeup = new LinUnexpectedWakeup;
        linUnexpectedWakeup->time = std::stod(match[1]);
        linUnexpectedWakeup->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        if (match[3] != "") {
            if (match[4] != "")
                linUnexpectedWakeup->width = std::stoul(match[5]);
            if (match[6] != "")
                linUnexpectedWakeup->wakeupByte = std::stoul(match[7]);
        }
        linUnexpectedWakeup->startOfFrame = std::stod(match[8]);
        linUnexpectedWakeup->baudrate = std::stoul(match[9]);
        return linUnexpectedWakeup;
    }

    return nullptr;
}

void LinUnexpectedWakeup::write(File & file, std::ostream & stream) {
    if (file.version < File::Version::Ver_7_5)
        return;

    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s Unexpected wakeup: "*/
    writeLinChannel(file, stream, channel);
    stream << " Unexpected wakeup: ";

    if (width > 0) {
        /* LIN 2.x */
        stream << "approx. " << std::dec << width << " us";
    } else {
        /* LIN 1.x */
        switch (file.base) {
        case 10:
            /* format: "Signal = %3d" */
            stream << "Signal = " << std::setw(3) << std::dec << (uint16_t) wakeupByte;
            break;
        case 16:
            /* format: "Signal = %02X" */
            stream << "Signal = " << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) wakeupByte;
            break;
        }
    }

    writeLinStartOfFrame(file, stream, startOfFrame);
    writeLinBaudrate(file, stream, baudrate);

    stream << endl;
}

}
}
