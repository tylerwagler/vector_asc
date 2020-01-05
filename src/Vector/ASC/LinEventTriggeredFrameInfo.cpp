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

#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinEventTriggeredFrameInfo.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinEventTriggeredFrameInfo * LinEventTriggeredFrameInfo::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS REGEX_LIN_ID
                     REGEX_WS "EvTrigFrmInfo" REGEX_WS REGEX_LIN_ETFName REGEX_WS REGEX_LIN_description REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linEventTriggeredFrameInfo = new LinEventTriggeredFrameInfo;
        linEventTriggeredFrameInfo->time = std::stod(match[1]);
        linEventTriggeredFrameInfo->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linEventTriggeredFrameInfo->id = match[3];
        linEventTriggeredFrameInfo->etfName = match[4];
        linEventTriggeredFrameInfo->description = match[5];
        return linEventTriggeredFrameInfo;
    }

    return nullptr;
}

void LinEventTriggeredFrameInfo::write(File & file, std::ostream & stream) {
    if (file.version > File::Version::Ver_5_2)
        return;

    writeLinTime(file, stream, time);
    stream << ' ';
    writeLinChannel(file, stream, channel);
    stream << ' ' << id << ' ';

    /* format: "EvTrigFrmInfo" */
    stream << "EvTrigFrmInfo";

    stream
            << ' ' << etfName
            << ' ' << description;

    stream << endl;
}

}
}
