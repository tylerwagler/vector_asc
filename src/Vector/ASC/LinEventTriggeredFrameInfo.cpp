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
#include "LinEventTriggeredFrameInfo.h"

namespace Vector {
namespace ASC {

LinEventTriggeredFrameInfo::LinEventTriggeredFrameInfo() :
    Event(),
    time(0.0),
    channel(0),
    id(),
    etfName(),
    description()
{
    eventType = EventType::LinEventTriggeredFrameInfo;
}

LinEventTriggeredFrameInfo::~LinEventTriggeredFrameInfo()
{
}

LinEventTriggeredFrameInfo * LinEventTriggeredFrameInfo::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " ([[:xdigit:]]+)"
                " EvTrigFrmInfo"
                " ([[:alnum:]_]+)"
                " (.*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinEventTriggeredFrameInfo * linEventTriggeredFrameInfo = new LinEventTriggeredFrameInfo;
        linEventTriggeredFrameInfo->time = std::stod(match[1]);
        linEventTriggeredFrameInfo->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linEventTriggeredFrameInfo->id = match[3];
        linEventTriggeredFrameInfo->etfName = match[4];
        linEventTriggeredFrameInfo->description = match[5];
        return linEventTriggeredFrameInfo;
    }

    return nullptr;
}

void LinEventTriggeredFrameInfo::write(File & file, std::ostream & stream)
{
}

}
}
