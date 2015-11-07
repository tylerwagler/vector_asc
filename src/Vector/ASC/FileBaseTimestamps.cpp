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
    std::regex regex(
                "^base ((hex)|(dec)) "
                " timestamps ((absolute)|(relative))$");
    std::smatch match;
    if (std::regex_search(line, match, regex)) {
        FileBaseTimestamps * fileBaseTimestamps = new FileBaseTimestamps;
        fileBaseTimestamps->base = ((match[1] == "hex") ? Base::Hex : Base::Dec);
        fileBaseTimestamps->timestamps = ((match[2] == "absolute") ? Timestamps::Absolute : Timestamps::Relative);
        return fileBaseTimestamps;
    }

    return nullptr;
}

void FileBaseTimestamps::write(File & file, std::ostream & stream)
{
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
