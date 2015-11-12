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
#include "LinSyncError.h"

namespace Vector {
namespace ASC {

LinSyncError::LinSyncError() :
    Event(),
    time(0.0),
    channel(0),
    timeInterval(),
    startOfFrame(0.0),
    baudrate(0),
    syncBreak(0),
    syncDel(0)
{
    eventType = EventType::LinSyncError;
}

LinSyncError::~LinSyncError()
{
}

LinSyncError * LinSyncError::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:digit:]]+)"
                " SyncError"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                "( SOF = ([[:digit:].]+))?"
                "( BR = ([[:digit:]]+))?"
                "( break = ([[:digit:]]+) ([[:digit:]]+))?$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinSyncError * linSyncError = new LinSyncError;
        linSyncError->time = std::stod(match[1]);
        linSyncError->channel = std::stoul(match[2]);
        linSyncError->timeInterval[0] = std::stoul(match[3]);
        linSyncError->timeInterval[1] = std::stoul(match[4]);
        linSyncError->timeInterval[2] = std::stoul(match[5]);
        linSyncError->timeInterval[3] = std::stoul(match[6]);
        linSyncError->startOfFrame = std::stod(match[8]);
        linSyncError->baudrate = std::stoul(match[10]);
        linSyncError->syncBreak = std::stoul(match[12]);
        linSyncError->syncDel = std::stoul(match[13]);
        return linSyncError;
    }

    return nullptr;
}

void LinSyncError::write(File & file, std::ostream & stream)
{
}

}
}
