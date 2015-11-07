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
#include "GpsEvent.h"

namespace Vector {
namespace ASC {

GpsEvent::GpsEvent() :
    Event(),
    time(0.0),
    channel(0),
    latitude(0.0),
    longitude(0.0),
    altitude(0.0),
    speed(0.0),
    course(0.0)
{
    eventType = EventType::GpsEvent;
}

GpsEvent::~GpsEvent()
{
}

GpsEvent * GpsEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " GPS-Device: ([[:digit:]]+)"
                " La: ([[:digit:].]+)"
                " Lo: ([[:digit:].]+)"
                " Alt: ([[:digit:].]+)"
                " Sp: ([[:digit:].]+)"
                " Co: ([[:digit:].]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        GpsEvent * gpsEvent = new GpsEvent;
        gpsEvent->time = std::stof(match[1]);
        gpsEvent->channel = std::stoul(match[2]);
        gpsEvent->latitude = std::stof(match[3]);
        gpsEvent->longitude = std::stof(match[4]);
        gpsEvent->altitude = std::stof(match[5]);
        gpsEvent->speed = std::stof(match[6]);
        gpsEvent->course = std::stof(match[7]);
        return gpsEvent;
    }

    return nullptr;
}

void GpsEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << " GPS-Device: " << channel
            << " La: " << latitude
            << " Lo: " << longitude
            << " Alt: " << altitude
            << " Sp: " << speed
            << " Co: " << course
            << endl;
}

}
}
