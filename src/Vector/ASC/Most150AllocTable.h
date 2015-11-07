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

/** MOST50/150 Allocation Table */
/* <Time> <Channel> AT150: <AT150EventModeFlags> <FreeBytes> <AT150Size> <W0>... <WAT150Size-1> */
class Most150AllocTable : public Event
{
public:
    Most150AllocTable();
    virtual ~Most150AllocTable();

    /** Time */
    float time;

    /** Channel */
    unsigned short channel;

    /** AT150EventModeFlags */
    unsigned short at150EventModeFlags;

    /** FreeBytes */
    unsigned short freeBytes;

    /** AT150Size */
    unsigned short at150Size;

    /** W */
    unsigned short w[1024];

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static Most150AllocTable * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
