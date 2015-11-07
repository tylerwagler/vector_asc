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

/** System Variables Event */
/* <Time> SV: <svtype> <flag> <flag> <path> = <value> */
/* <Time> SV: <svtype> <flag> <flag> <path> = <valuetype><count> <value> */
class SystemVariablesEvent : public Event
{
public:
    SystemVariablesEvent();
    virtual ~SystemVariablesEvent();

    /** Time */
    float time;

    /** a number which represents the variable data type */
    enum class Svtype : uint32_t {
        /** Float */
        Float = 1,

        /** Int */
        Int = 2,

        /** String */
        String = 3,

        /** Float array */
        FloatArray = 4,

        /** Int array */
        IntArray = 5
    };

    /** a number which represents the variable data type */
    Svtype svtype;

    /** two flags: Unused. */
    bool flag[2];

    /** the full path (name with namespace) of the system variable */
    std::string path;

    /** the value as number or string (depend on variable data type). */
    std::string value;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static SystemVariablesEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
