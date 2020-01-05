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
#include <Vector/ASC/SystemVariables.h>

namespace Vector {
namespace ASC {

SystemVariables * SystemVariables::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "SV:" REGEX_ws REGEX_svtype REGEX_WS "0" REGEX_WS "0"
                     REGEX_WS "(.+?)" REGEX_ws "=" REGEX_ws "(.+?)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * systemVariables = new SystemVariables;
        systemVariables->time = std::stod(match[1]);
        switch (std::stoul(match[2])) {
        case 1:
            systemVariables->svtype = Svtype::Float;
            break;
        case 2:
            systemVariables->svtype = Svtype::Int;
            break;
        case 3:
            systemVariables->svtype = Svtype::String;
            break;
        case 4:
            systemVariables->svtype = Svtype::FloatArray;
            break;
        case 5:
            systemVariables->svtype = Svtype::IntArray;
            break;
        }
        systemVariables->path = match[3];
        systemVariables->value = match[4];
        return systemVariables;
    }

    return nullptr;
}

void SystemVariables::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << "    ";

    /* format: "SV: %d %d %d %s = " */
    stream
            << "SV: " << (uint16_t) svtype
            << ' ' << (flag[0] ? '1' : '0')
            << ' ' << (flag[1] ? '1' : '0')
            << ' ' << path
            << " = ";

    stream << value;

    stream << endl;
}

}
}
