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

#include <Vector/ASC/CanCommon.h>
#include <Vector/ASC/CanSymbolsRegEx.h>
#include <Vector/ASC/FileVersion.h>

namespace Vector {
namespace ASC {

FileVersion * FileVersion::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL "//" REGEX_ws "version" REGEX_WS "([[:digit:]]{1,3})\\.([[:digit:]]{1,3})\\.([[:digit:]]{1,3})" REGEX_ENDL);
    std::smatch match;
    if (std::regex_search(line, match, regex)) {
        auto * fileVersion = new FileVersion;
        fileVersion->versionMajor = std::stoul(match[1]);
        fileVersion->versionMinor = std::stoul(match[2]);
        fileVersion->versionPatch = std::stoul(match[3]);
        return fileVersion;
    }

    return nullptr;
}

void FileVersion::write(File & /*file*/, std::ostream & stream) {
    /* format: "// version %d.%d.%d" */
    stream
            << "// version"
            << ' ' << std::dec << (int16_t) versionMajor
            << '.' << std::dec << (int16_t) versionMinor
            << '.' << std::dec << (int16_t) versionPatch;

    stream << endl;
}

}
}
