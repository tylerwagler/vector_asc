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
#include <Vector/ASC/FileInternalEventsLogged.h>

namespace Vector {
namespace ASC {

FileInternalEventsLogged * FileInternalEventsLogged::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL "(no )?internal events logged" REGEX_ENDL);
    std::smatch match;
    if (std::regex_search(line, match, regex)) {
        auto * fileInternalEventsLogged = new FileInternalEventsLogged;
        fileInternalEventsLogged->internalEventsLogged = (match[1] == "");
        return fileInternalEventsLogged;
    }

    return nullptr;
}

void FileInternalEventsLogged::write(File & /*file*/, std::ostream & stream) {
    if (!internalEventsLogged)
        stream << "no ";

    /* format: "internal events logged" */
    stream << "internal events logged";

    stream << endl;
}

}
}
