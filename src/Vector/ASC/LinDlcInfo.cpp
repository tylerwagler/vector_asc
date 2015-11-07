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
#include "LinDlcInfo.h"

namespace Vector {
namespace ASC {

LinDlcInfo::LinDlcInfo() :
    Event(),
    time(0.0),
    channel(),
    id(0),
    dlc(0)
{
    eventType = EventType::LinDlcInfo;
}

LinDlcInfo::~LinDlcInfo()
{
}

LinDlcInfo * LinDlcInfo::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " ([[:digit:]]+)"
                " DlcInfo"
                " ([[:digit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinDlcInfo * linDlcInfo = new LinDlcInfo;
        linDlcInfo->time = std::stof(match[1]);
        linDlcInfo->channel = match[2];
        linDlcInfo->id = std::stoul(match[3]);
        linDlcInfo->dlc = std::stoul(match[4]);
        return linDlcInfo;
    }

    return nullptr;
}

void LinDlcInfo::write(File & file, std::ostream & stream)
{
}

}
}
