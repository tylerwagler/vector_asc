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
#include "CanOverloadFrame.h"
#include "CanSymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanOverloadFrame::CanOverloadFrame() :
    Event(),
    time(0.0),
    channel(0)
{
    eventType = EventType::CanOverloadFrame;
}

CanOverloadFrame::~CanOverloadFrame()
{
}

CanOverloadFrame * CanOverloadFrame::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS REGEX_Channel REGEX_WS "OverloadFrame" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanOverloadFrame * canOverloadFrame = new CanOverloadFrame;
        canOverloadFrame->time = std::stod(match[1]);
        canOverloadFrame->channel = std::stoul(match[2]);
        return canOverloadFrame;
    }

    return nullptr;
}

void CanOverloadFrame::write(File & file, std::ostream & stream)
{
    writeTime(file, stream, time);
    stream << ' ' << channel << "  ";

    /* format: "OverloadFrame" */
    stream << "OverloadFrame";

    stream << endl;
}

}
}
