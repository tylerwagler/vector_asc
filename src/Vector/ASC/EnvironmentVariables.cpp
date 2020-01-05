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
#include <Vector/ASC/EnvironmentVariables.h>

namespace Vector {
namespace ASC {

EnvironmentVariables * EnvironmentVariables::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "(.+?)" REGEX_ws ":=" REGEX_ws "(.+?)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * environmentVariables = new EnvironmentVariables;
        environmentVariables->time = std::stod(match[1]);
        environmentVariables->evname = match[2];
        environmentVariables->value = match[3];
        return environmentVariables;
    }

    return nullptr;
}

void EnvironmentVariables::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << "    " << std::left << std::setw(12) << evname << " := " << value;

    stream << endl;
}

}
}
