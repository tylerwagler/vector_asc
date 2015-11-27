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
#include "LinWakeupFrame.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

LinWakeupFrame::LinWakeupFrame() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    wakeupByte(0),
    startOfFrame(0),
    baudrate(0),
    wakeupLengthInfo(0)
{
    eventType = EventType::LinWakeupFrame;
}

LinWakeupFrame::~LinWakeupFrame()
{
}

LinWakeupFrame * LinWakeupFrame::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS "WakeupFrame"
                     REGEX_WS REGEX_LIN_Dir REGEX_WS REGEX_LIN_WakeupByte
                     "(" REGEX_WS "SOF" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame
                     REGEX_WS "BR" REGEX_ws "=" REGEX_ws REGEX_LIN_baudrate
                     REGEX_WS "LengthCode" REGEX_ws "=" REGEX_ws REGEX_LIN_WakeupLengthInfo ")?" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinWakeupFrame * linWakeupFrame = new LinWakeupFrame;
        linWakeupFrame->time = std::stod(match[1]);
        linWakeupFrame->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        if (match[3] == "Rx")
            linWakeupFrame->dir = Dir::Rx;
        else
        if (match[3] == "Tx")
            linWakeupFrame->dir = Dir::Tx;
        linWakeupFrame->wakeupByte = std::stoul(match[4], nullptr, file.base);
        if (match[5] != "") {
            linWakeupFrame->startOfFrame = std::stod(match[6]);
            linWakeupFrame->baudrate = std::stoul(match[7]);
            linWakeupFrame->wakeupLengthInfo = std::stoul(match[8]);
        }
        return linWakeupFrame;
    }

    return nullptr;
}

void LinWakeupFrame::write(File & file, std::ostream & stream)
{
}

}
}
