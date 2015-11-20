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
#include "MostCommonRegisterEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

MostCommonRegisterEvent::MostCommonRegisterEvent() :
    Event(),
    time(0.0),
    channel(0),
    regSubType(MostRegSubType::Unspecified),
    regChip(0),
    regOffset(0),
    regDataLen(0),
    data()
{
    eventType = EventType::MostCommonRegisterEvent;
}

MostCommonRegisterEvent::~MostCommonRegisterEvent()
{
}

MostCommonRegisterEvent * MostCommonRegisterEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "RegData:"
                     REGEX_ws REGEX_MOST_RegSubType REGEX_WS REGEX_MOST_RegChip REGEX_WS REGEX_MOST_RegOffset
                     REGEX_WS REGEX_MOST_RegDataLen
                     "((" REGEX_WS REGEX_MOST_Dx ")*)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostCommonRegisterEvent * mostCommonRegisterEvent = new MostCommonRegisterEvent;
        mostCommonRegisterEvent->time = std::stod(match[1]);
        mostCommonRegisterEvent->channel = std::stoul(match[2]);
        switch(std::stoul(match[3])) {
        case 0:
            mostCommonRegisterEvent->regSubType = MostRegSubType::Unspecified;
            break;
        case 1:
            mostCommonRegisterEvent->regSubType = MostRegSubType::Notify;
            break;
        case 2:
            mostCommonRegisterEvent->regSubType = MostRegSubType::ReadRequest;
            break;
        case 3:
            mostCommonRegisterEvent->regSubType = MostRegSubType::WriteRequest;
            break;
        case 4:
            mostCommonRegisterEvent->regSubType = MostRegSubType::ReadResult;
            break;
        case 5:
            mostCommonRegisterEvent->regSubType = MostRegSubType::WriteResult;
            break;
        case 6:
            mostCommonRegisterEvent->regSubType = MostRegSubType::ReadFailed;
            break;
        case 7:
            mostCommonRegisterEvent->regSubType = MostRegSubType::WriteFailed;
            break;
        }
        mostCommonRegisterEvent->regChip = std::stoul(match[4], nullptr, 16);
        mostCommonRegisterEvent->regOffset = std::stoul(match[5], nullptr, 16);
        mostCommonRegisterEvent->regDataLen = std::stoul(match[6], nullptr, 16);
        std::istringstream iss(match[7]);
        iss >> std::hex;
        for (uint8_t i = 0; !iss.eof(); ++i) {
            unsigned short s;
            iss >> s;
            mostCommonRegisterEvent->data[i] = s;
        }
        return mostCommonRegisterEvent;
    }

    return nullptr;
}

void MostCommonRegisterEvent::write(File & file, std::ostream & stream)
{
}

}
}
