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
#include <Vector/ASC/FileBaseTimestamps.h>

namespace Vector {
namespace ASC {

FileBaseTimestamps * FileBaseTimestamps::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL "base" REGEX_WS "(hex|dec)" REGEX_WS "timestamps" REGEX_WS "(absolute|relative)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_search(line, match, regex)) {
        auto * fileBaseTimestamps = new FileBaseTimestamps;
        if (match[1] == "hex")
            fileBaseTimestamps->base = File::Base::Hex;
        else if (match[1] == "dec")
            fileBaseTimestamps->base = File::Base::Dec;
        if (match[2] == "absolute")
            fileBaseTimestamps->timestamps = File::Timestamps::Absolute;
        else if (match[2] == "relative")
            fileBaseTimestamps->timestamps = File::Timestamps::Relative;
        return fileBaseTimestamps;
    }

    return nullptr;
}

void FileBaseTimestamps::write(File & /*file*/, std::ostream & stream) {
    /* format: "base %s  timestamps %s" */
    stream
            << "base "
            << (base == File::Base::Dec ? "dec" : "hex")
            << "  timestamps "
            << (timestamps == File::Timestamps::Absolute ? "absolute" : "relative");

    stream << endl;
}

}
}
