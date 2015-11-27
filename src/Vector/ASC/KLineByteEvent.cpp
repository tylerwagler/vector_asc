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
#include "KLineByteEvent.h"
#include "KLineCommon.h"
#include "KLineSymbolsRegEx.h"

namespace Vector {
namespace ASC {

KLineByteEvent::KLineByteEvent() :
    Event(),
    time(0.0),
    port(),
    direction(Dir::Rx),
    baudrate(0),
    length(0),
    data()
{
    eventType = EventType::KLineByteEvent;
}

KLineByteEvent::~KLineByteEvent()
{
}

KLineByteEvent * KLineByteEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_KLine_time REGEX_WS REGEX_KLine_port REGEX_WS REGEX_KLine_direction
                     REGEX_WS REGEX_KLine_baudrate REGEX_WS REGEX_KLine_length
                     "((" REGEX_WS REGEX_KLine_data ")*)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        KLineByteEvent * kLineByteEvent = new KLineByteEvent;
        kLineByteEvent->time = std::stod(match[1]);
        kLineByteEvent->port = match[2];
        if (match[4] == "Rx")
                kLineByteEvent->direction = Dir::Rx;
        else
        if (match[4] == "Tx")
                kLineByteEvent->direction = Dir::Tx;
        kLineByteEvent->baudrate = std::stoul(match[5]);
        kLineByteEvent->length = std::stoul(match[6]);
        std::istringstream iss(match[7]);
        if (file.base == 10)
            iss >> std::dec;
        if (file.base == 16)
            iss >> std::hex;
        for (uint8_t i = 0; i < kLineByteEvent->length; ++i) {
            unsigned short s;
            iss >> s;
            kLineByteEvent->data[i] = s;
        }
        return kLineByteEvent;
    }

    return nullptr;
}

void KLineByteEvent::write(File & file, std::ostream & stream)
{
    stream << endl;
}

}
}
