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

#include <Vector/ASC/LinChecksumInfo.h>
#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinChecksumInfo * LinChecksumInfo::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS REGEX_LIN_ID REGEX_WS "CSInfo"
                     REGEX_WS REGEX_LIN_checksumModelInfo REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linChecksumInfo = new LinChecksumInfo;
        linChecksumInfo->time = std::stod(match[1]);
        linChecksumInfo->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linChecksumInfo->id = match[3];
        if (match[4] == "classic")
            linChecksumInfo->checksumModelInfo = LinChecksumModelInfo::Classic;
        else if (match[4] == "enhanced")
            linChecksumInfo->checksumModelInfo = LinChecksumModelInfo::Enhanced;
        return linChecksumInfo;
    }

    return nullptr;
}

void LinChecksumInfo::write(File & file, std::ostream & stream) {
    /* format: "%s %-12.1x CSInfo    %s" */
    /* format: "%s %-12.1d CSInfo    %s" */
    /* format: "%s %s CSInfo    %s" */
    writeLinTime(file, stream, time);
    stream << ' ';
    writeLinChannel(file, stream, channel);
    stream << ' ';
    stream << std::left << std::setw(12) << id;
    stream << " CSInfo    ";
    switch (checksumModelInfo) {
    case LinChecksumModelInfo::Classic:
        /* format: "Using classic checksum" */
        stream << "Using classic checksum";
        break;
    case LinChecksumModelInfo::Enhanced:
        /* format: "Using enhanced checksum" */
        stream << "Using enhanced checksum";
        break;
    }

    stream << endl;
}

}
}
