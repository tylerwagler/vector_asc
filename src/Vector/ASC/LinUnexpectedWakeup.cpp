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
#include "LinUnexpectedWakeup.h"

namespace Vector {
namespace ASC {

LinUnexpectedWakeup::LinUnexpectedWakeup() :
    Event(),
    time(0.0),
    channel(),
    width(0),
    startOfFrame(0),
    baudrate(0),
    wakeupByte(0)
{
    eventType = EventType::LinUnexpectedWakeup;
}

LinUnexpectedWakeup::~LinUnexpectedWakeup()
{
}

LinUnexpectedWakeup * LinUnexpectedWakeup::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " Unexpected wakeup:"
                "( approx\\. ([[:digit:]]+) us)?"
                "( Signal = ([[:digit:]]+))?"
                " SOF = ([[:digit:].]+)"
                " BR = ([[:digit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinUnexpectedWakeup * linUnexpectedWakeup = new LinUnexpectedWakeup;
        linUnexpectedWakeup->time = std::stof(match[1]);
        linUnexpectedWakeup->channel = match[2];
        linUnexpectedWakeup->width = std::stoul(match[4]);
        if (match[5] != "")
            linUnexpectedWakeup->wakeupByte = std::stoul(match[6]);
        linUnexpectedWakeup->startOfFrame = std::stof(match[7]);
        linUnexpectedWakeup->baudrate = std::stoul(match[8]);
        return linUnexpectedWakeup;
    }

    return nullptr;
}

void LinUnexpectedWakeup::write(File & file, std::ostream & stream)
{
}

}
}
