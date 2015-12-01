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
#include "KLineCommon.h"
#include "KLineMessage.h"
#include "KLineSymbolsRegEx.h"

namespace Vector {
namespace ASC {

KLineMessage::KLineMessage() :
    Event(),
    time(0.0),
    port(),
    direction(Dir::Rx),
    baudrate(0),
    source(),
    destination(),
    length(0),
    data()
{
    eventType = EventType::KLineMessage;
}

KLineMessage::~KLineMessage()
{
}

KLineMessage * KLineMessage::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL "//" REGEX_ws "K-Line:" REGEX_ws REGEX_KLine_time REGEX_WS REGEX_KLine_port
                     REGEX_WS REGEX_KLine_direction REGEX_WS REGEX_KLine_baudrate REGEX_WS REGEX_KLine_source
                     REGEX_WS REGEX_KLine_destination REGEX_WS REGEX_KLine_length
                     "((" REGEX_WS REGEX_KLine_data ")*)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        KLineMessage * kLineMessage = new KLineMessage;
        kLineMessage->time = std::stod(match[1]);
        kLineMessage->port = match[2];
        if (match[4] == "Rx")
                kLineMessage->direction = Dir::Rx;
        else
        if (match[4] == "Tx")
                kLineMessage->direction = Dir::Tx;
        kLineMessage->baudrate = std::stoul(match[5]);
        kLineMessage->source = match[6];
        kLineMessage->destination = match[7];
        kLineMessage->length = std::stoul(match[8]);
        std::istringstream iss(match[9]);
        if (file.base == 10)
            iss >> std::dec;
        if (file.base == 16)
            iss >> std::hex;
        for (uint8_t i = 0; i < kLineMessage->length; ++i) {
            unsigned short s;
            iss >> s;
            kLineMessage->data[i] = s;
        }
        return kLineMessage;
    }

    return nullptr;
}

void KLineMessage::write(File & file, std::ostream & stream)
{
    /* format: "// K-Line: " */
    stream << "// K-Line: ";

    stream << std::fixed << time << ' ' << port << ' ';
    writeKLineDirection(file, stream, direction);
    stream << ' ' << std::dec << baudrate;
    stream << ' ' << std::dec << source;
    stream << ' ' << std::dec << destination;
    stream << ' ' << std::dec << length;
    for (int i = 0; i < length; ++i)
        stream << ' ' << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) data[i];

    stream << endl;
}

}
}
