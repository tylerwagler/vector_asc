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
#include <Vector/ASC/Gps.h>

namespace Vector {
namespace ASC {

Gps * Gps::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "GPS-Device:" REGEX_ws "([[:digit:]]+)"
                     REGEX_WS "La:" REGEX_ws "([[:digit:].]+)"
                     REGEX_WS "Lo:" REGEX_ws "([[:digit:].]+)"
                     REGEX_WS "Alt:" REGEX_ws "([[:digit:].]+)"
                     REGEX_WS "Sp:" REGEX_ws "([[:digit:].]+)"
                     REGEX_WS "Co:" REGEX_ws "([[:digit:].]+)"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        Gps * gps = new Gps;
        gps->time = std::stod(match[1]);
        gps->channel = std::stoul(match[2]);
        gps->latitude = std::stod(match[3]);
        gps->longitude = std::stod(match[4]);
        gps->altitude = std::stod(match[5]);
        gps->speed = std::stod(match[6]);
        gps->course = std::stod(match[7]);
        return gps;
    }

    return nullptr;
}

void Gps::write(File & file, std::ostream & stream) {
    /* format: "%f GPS-Device: %d    La: %lf    Lo: %lf    Alt: %lf    Sp: %lf    Co: %lf" */
    writeTime(file, stream, time);
    stream
            << " GPS-Device: " << channel
            << "    La: " << latitude
            << "    Lo: " << longitude
            << "    Alt: " << altitude
            << "    Sp: " << speed
            << "    Co: " << course;

    stream << endl;
}

}
}
