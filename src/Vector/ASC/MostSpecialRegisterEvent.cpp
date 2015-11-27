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
#include "MostCommon.h"
#include "MostSpecialRegisterEvent.h"
#include "MostSymbolsRegEx.h"

namespace Vector {
namespace ASC {

MostSpecialRegisterEvent::MostSpecialRegisterEvent() :
    Event(),
    time(0.0),
    channel(0),
    regSubType(MostRegSubType::Unspecified),
    regId(0),
    regValue(0)
{
    eventType = EventType::MostSpecialRegisterEvent;
}

MostSpecialRegisterEvent::~MostSpecialRegisterEvent()
{
}

MostSpecialRegisterEvent * MostSpecialRegisterEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "Register:"
                     REGEX_ws REGEX_MOST_RegSubType REGEX_WS REGEX_MOST_RegID REGEX_WS REGEX_MOST_RegValue REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostSpecialRegisterEvent * mostSpecialRegisterEvent = new MostSpecialRegisterEvent;
        mostSpecialRegisterEvent->time = std::stod(match[1]);
        mostSpecialRegisterEvent->channel = std::stoul(match[2]);
        switch(std::stoul(match[3])) {
        case 0:
            mostSpecialRegisterEvent->regSubType = MostRegSubType::Unspecified;
            break;
        case 1:
            mostSpecialRegisterEvent->regSubType = MostRegSubType::Notify;
            break;
        case 2:
            mostSpecialRegisterEvent->regSubType = MostRegSubType::ReadRequest;
            break;
        case 3:
            mostSpecialRegisterEvent->regSubType = MostRegSubType::WriteRequest;
            break;
        case 4:
            mostSpecialRegisterEvent->regSubType = MostRegSubType::ReadResult;
            break;
        case 5:
            mostSpecialRegisterEvent->regSubType = MostRegSubType::WriteResult;
            break;
        case 6:
            mostSpecialRegisterEvent->regSubType = MostRegSubType::ReadFailed;
            break;
        case 7:
            mostSpecialRegisterEvent->regSubType = MostRegSubType::WriteFailed;
            break;
        }
        mostSpecialRegisterEvent->regId = std::stoul(match[4], nullptr, 16);
        mostSpecialRegisterEvent->regValue = std::stoul(match[5], nullptr, 16);
        return mostSpecialRegisterEvent;
    }

    return nullptr;
}

void MostSpecialRegisterEvent::write(File & file, std::ostream & stream)
{
    writeMostTime(file, stream, time);
    stream << ' ';
    writeMostChannel(file, stream, channel);
    stream << ' ';

    /* format: "Register: %1X %02X %012I64X" */
    /* format: "Register: %1X %02X %04I64X" */
    stream
            << "Register: "
            << std::setw(1) << std::uppercase << std::hex << (uint16_t) regSubType
            << ' '
            << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) regId
            << ' '
            << std::setfill('0') << std::setw(4 /* @todo or 16 */) << std::uppercase << std::hex << (uint16_t) regValue;

    stream << endl;
}

}
}
