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
#include <Vector/ASC/StartOfMeasurement.h>

namespace Vector {
namespace ASC {

StartOfMeasurement * StartOfMeasurement::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "((Start of measurement)|(Start der Messung))" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * startOfMeasurement = new StartOfMeasurement;
        startOfMeasurement->time = std::stod(match[1]);
        if (match[2] == "Start of measurement")
            startOfMeasurement->language = File::Language::En;
        else if (match[2] == "Start der Messung")
            startOfMeasurement->language = File::Language::De;
        return startOfMeasurement;
    }

    return nullptr;
}

void StartOfMeasurement::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << ' ';

    if (file.language == File::Language::En)
        stream << "Start of measurement";
    else
        stream << "Start der Messung";

    stream << endl;
}

}
}
