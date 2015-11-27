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
#include "CanCommon.h"
#include "CanSymbolsRegEx.h"
#include "FileBaseTimestamps.h"

namespace Vector {
namespace ASC {

FileBaseTimestamps::FileBaseTimestamps() :
    Event(),
    base(Base::Hex),
    timestamps(Timestamps::Absolute)
{
    eventType = EventType::FileBaseTimestamps;
}

FileBaseTimestamps::~FileBaseTimestamps()
{
}

FileBaseTimestamps * FileBaseTimestamps::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL "base" REGEX_WS "(hex|dec)" REGEX_WS "timestamps" REGEX_WS "(absolute|relative)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_search(line, match, regex)) {
        FileBaseTimestamps * fileBaseTimestamps = new FileBaseTimestamps;
        if (match[1] == "hex")
            fileBaseTimestamps->base = Base::Hex;
        else
        if (match[1] == "dec")
            fileBaseTimestamps->base = Base::Dec;
        if (match[2] == "absolute")
            fileBaseTimestamps->timestamps = Timestamps::Absolute;
        else
        if (match[2] == "relative")
            fileBaseTimestamps->timestamps = Timestamps::Relative;
        return fileBaseTimestamps;
    }

    return nullptr;
}

void FileBaseTimestamps::write(File & file, std::ostream & stream)
{
    /* format: "base %s  timestamps %s" */
    stream << "base ";
    switch(base) {
    case Base::Hex:
        stream << "hex";
        break;
    case Base::Dec:
        stream << "dec";
        break;
    }
    stream << "  timestamps ";
    switch(timestamps) {
    case Timestamps::Absolute:
        stream << "absolute";
        break;
    case Timestamps::Relative:
        stream << "relative";
        break;
    }

    stream << endl;
}

}
}
