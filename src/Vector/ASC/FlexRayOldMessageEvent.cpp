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
#include "FlexRayCommon.h"
#include "FlexRayOldMessageEvent.h"
#include "FlexRaySymbolsRegEx.h"

namespace Vector {
namespace ASC {

FlexRayOldMessageEvent::FlexRayOldMessageEvent() :
    Event(),
    time(0.0),
    channel(),
    id(0),
    cycle(0),
    nm(false),
    sync(false),
    headerCrc(0),
    symbolicName(),
    dlc(0),
    data(),
    frameState(0),
    headerBitMask(0)
{
    eventType = EventType::FlexRayOldMessageEvent;
}

FlexRayOldMessageEvent::~FlexRayOldMessageEvent()
{
}

FlexRayOldMessageEvent * FlexRayOldMessageEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_FlexRayOld_Time REGEX_WS REGEX_FlexRayOld_Channel REGEX_WS "V9"
                     REGEX_WS REGEX_FlexRayOld_ID REGEX_WS REGEX_FlexRayOld_Cycle REGEX_WS REGEX_FlexRayOld_NM
                     REGEX_WS REGEX_FlexRayOld_Sync REGEX_WS REGEX_FlexRayOld_HeaderCRC
                     REGEX_WS REGEX_FlexRayOld_SymbolicName REGEX_WS REGEX_FlexRayOld_DLC
                     "((" REGEX_WS REGEX_FlexRayOld_Dx "){0,255})" REGEX_WS REGEX_FlexRayOld_FrameState
                     REGEX_WS REGEX_FlexRayOld_HeaderBitMask REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayOldMessageEvent * flexRayOldMessageEvent = new FlexRayOldMessageEvent;
        flexRayOldMessageEvent->time = std::stod(match[1]);
        flexRayOldMessageEvent->channel = std::string(match[2])[0];
        flexRayOldMessageEvent->id = std::stoul(match[3]);
        flexRayOldMessageEvent->cycle = std::stoul(match[4]);
        flexRayOldMessageEvent->nm = (match[5] == '1');
        flexRayOldMessageEvent->sync = (match[6] == '1');
        flexRayOldMessageEvent->headerCrc = std::stoul(match[7]);
        flexRayOldMessageEvent->symbolicName = match[8];
        flexRayOldMessageEvent->dlc = std::stoul(match[9]);
        std::istringstream iss(match[10]);
        for (uint8_t i = 0; i < flexRayOldMessageEvent->dlc && i <= 255; ++i) {
            unsigned short s;
            iss >> s;
            flexRayOldMessageEvent->data[i] = s;
        }
        flexRayOldMessageEvent->frameState = std::stoul(match[12], nullptr, 16);
        flexRayOldMessageEvent->headerBitMask = std::stoul(match[13], nullptr, 16);
        return flexRayOldMessageEvent;
    }

    return nullptr;
}

void FlexRayOldMessageEvent::write(File & file, std::ostream & stream)
{
    stream << endl;
}

}
}
