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
#include "CanCommon.h"
#include "CanError.h"
#include "CanSymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanError::CanError() :
    Event(),
    time(0.0),
    channel(0),
    error()
{
    eventType = EventType::CanError;
}

CanError * CanError::read(File & /*file*/, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "CAN" REGEX_WS  REGEX_Channel REGEX_WS "Status:" REGEX_ws REGEX_Error REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanError * canError = new CanError;
        canError->time = std::stod(match[1]);
        canError->channel = std::stoul(match[2]);
        canError->error = match[3];
        return canError;
    }

    return nullptr;
}

void CanError::write(File & file, std::ostream & stream)
{
    writeTime(file, stream, time);

    if (file.version >= File::Version::Ver_8_0) {
        /* "format: "CAN %d Status: " */
        stream
                << " CAN " << std::dec << (int16_t) channel
                << " Status: ";
    } else {
        /* "format: "CAN %d Status: " */
        stream
                << " CAN " << std::dec << (int16_t) channel
                << " Status:";
    }

    /* format: "chip status busoff" */
    /* format: "chip status error passive" */
    /* format: "chip status error active" */
    /* format: "rx queue overrun" */
    /* format: "chip status warning level" */
    /* format: "hardware interface disconnected" */
    stream << error;

    stream << endl;
}

}
}
