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
#include <Vector/ASC/CanSymbolsRegEx.h>
#include <Vector/ASC/FileSplitInformation.h>

namespace Vector {
namespace ASC {

FileSplitInformation * FileSplitInformation::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL "//" REGEX_ws REGEX_Time REGEX_WS "previous log file:" REGEX_ws "(.+?)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * fileSplitInformation = new FileSplitInformation;
        fileSplitInformation->time = std::stod(match[1]);
        fileSplitInformation->fileName = match[2];
        return fileSplitInformation;
    }

    return nullptr;
}

void FileSplitInformation::write(File & /*file*/, std::ostream & stream) {
    stream << "// " << std::setw(8) << std::setprecision(4) << std::fixed << time;

    /* format: " previous log file: %s" */
    stream << " previous log file: " << fileName;

    stream << endl;
}

}
}
