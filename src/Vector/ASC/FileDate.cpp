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
#include <Vector/ASC/FileDate.h>

namespace Vector {
namespace ASC {

FileDate * FileDate::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL "date" REGEX_WS REGEX_WeekDay REGEX_WS REGEX_Month REGEX_WS REGEX_Date REGEX_WS REGEX_FullTime REGEX_WS REGEX_Year REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * fileDate = new FileDate;
        readDate(match[1], match[2], match[3], match[4], match[5], match[6], match[7], match[8],
                 fileDate->language, fileDate->date);
        return fileDate;
    }

    return nullptr;
}

void FileDate::write(File & file, std::ostream & stream) {
    /* format: "date %s" */
    stream << "date ";
    writeDate(file, stream, date);

    stream << endl;
}

}
}
