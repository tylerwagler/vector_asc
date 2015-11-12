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
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " WakeupFrame"
                " (Rx|Tx)"
                " ([[:digit:]]+)"
                " SOF = ([[:digit:].]+)"
                " BR = ([[:digit:]]+)"
                " LengthCode = ([[:digit:]]+)$");
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
        linWakeupFrame->wakeupByte = std::stoul(match[4]);
        linWakeupFrame->startOfFrame = std::stod(match[5]);
        linWakeupFrame->baudrate = std::stoul(match[6]);
        linWakeupFrame->wakeupLengthInfo = std::stoul(match[7]);
        return linWakeupFrame;
    }

    return nullptr;
}

void LinWakeupFrame::write(File & file, std::ostream & stream)
{
}

}
}
