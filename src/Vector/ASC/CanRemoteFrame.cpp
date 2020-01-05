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

#include <Vector/ASC/CanCommon.h>
#include <Vector/ASC/CanRemoteFrame.h>
#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

CanRemoteFrame * CanRemoteFrame::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS REGEX_Channel REGEX_WS REGEX_ID REGEX_WS REGEX_Dir REGEX_WS "r" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * canRemoteFrame = new CanRemoteFrame;
        canRemoteFrame->time = std::stod(match[1]);
        canRemoteFrame->channel = std::stoul(match[2]);
        canRemoteFrame->id = std::stoul(match[3], nullptr, 16);
        if (match[4] == "Rx")
            canRemoteFrame->dir = Dir::Rx;
        else if (match[4] == "Tx")
            canRemoteFrame->dir = Dir::Tx;
        return canRemoteFrame;
    }

    return nullptr;
}

void CanRemoteFrame::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << ' ' << std::dec << (uint16_t) channel << "  ";
    switch (file.base) {
    case 10:
        stream << std::left << std::setfill(' ') << std::setw(15) << std::dec << id;
        break;
    case 16:
        stream << std::left << std::setfill(' ') << std::setw(15) << std::hex << id;
        break;
    }
    stream << ' ';
    writeDir(file, stream, dir);
    stream << " r";

    stream << endl;
}

}
}
