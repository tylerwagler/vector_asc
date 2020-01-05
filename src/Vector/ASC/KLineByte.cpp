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
#include <sstream>

#include <Vector/ASC/KLineByte.h>
#include <Vector/ASC/KLineCommon.h>
#include <Vector/ASC/KLineSymbolsRegEx.h>

namespace Vector {
namespace ASC {

KLineByte * KLineByte::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_KLine_time REGEX_WS REGEX_KLine_port REGEX_WS REGEX_KLine_direction
                     REGEX_WS REGEX_KLine_baudrate REGEX_WS REGEX_KLine_length
                     "((" REGEX_WS REGEX_KLine_data ")*)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * kLineByte = new KLineByte;
        kLineByte->time = std::stod(match[1]);
        kLineByte->port = match[2];
        if (match[4] == "Rx")
            kLineByte->direction = Dir::Rx;
        else if (match[4] == "Tx")
            kLineByte->direction = Dir::Tx;
        kLineByte->baudrate = std::stoul(match[5]);
        kLineByte->length = std::stoul(match[6]);
        std::istringstream iss(match[7]);
        if (file.base == 10)
            iss >> std::dec;
        if (file.base == 16)
            iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            kLineByte->data.push_back(s);
        }
        return kLineByte;
    }

    return nullptr;
}

void KLineByte::write(File & file, std::ostream & stream) {
    writeKLineTime(file, stream, time);
    stream << "    " << port << ' ';
    writeKLineDirection(file, stream, direction);
    stream << ' ' << std::setfill(' ') << std::setw(6) << std::dec << baudrate;
    stream << "   " << std::setfill(' ') << std::setw(4) << std::dec << length;
    stream << "  ";
    stream << std::uppercase;
    writeData(file, stream, data);

    stream << endl;
}

}
}
