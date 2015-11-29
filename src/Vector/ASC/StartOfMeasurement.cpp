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
#include "StartOfMeasurement.h"

namespace Vector {
namespace ASC {

StartOfMeasurement::StartOfMeasurement() :
    Event(),
    time(0.0)
{
    eventType = EventType::StartOfMeasurement;
}

StartOfMeasurement::~StartOfMeasurement()
{
}

StartOfMeasurement * StartOfMeasurement::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "((Start of measurement)|(Start der Messung))" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        StartOfMeasurement * startOfMeasurement = new StartOfMeasurement;
        startOfMeasurement->time = std::stod(match[1]);
        return startOfMeasurement;
    }

    return nullptr;
}

void StartOfMeasurement::write(File & file, std::ostream & stream)
{
    writeTime(file, stream, time);
    stream << ' ';

    /* format: "Start der Messung" */
    /* format: "Start of measurement" */
    stream << "Start of measurement";

    stream << endl;
}

}
}
