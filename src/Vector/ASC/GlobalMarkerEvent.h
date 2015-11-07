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

#pragma once

#include "Event.h"

namespace Vector {
namespace ASC {

/** Global marker event */
/* <Time> <type> <background color> <foreground color> GMGroup: <group name> GMMarker: <marker name> GMDescription: <description> */
class GlobalMarkerEvent : public Event
{
public:
    GlobalMarkerEvent();
    virtual ~GlobalMarkerEvent();

    /** Time */
    float time;

    /** type */
    uint32_t type;

    /** background color */
    uint32_t backgroundColor;

    /** foreground color */
    uint32_t foregroundColor;

    /** relocatable */
    bool relocatable;

    /** group name */
    std::string groupName;

    /** marker name */
    std::string markerName;

    /** description */
    std::string description;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static GlobalMarkerEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
