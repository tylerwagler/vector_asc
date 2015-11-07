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

/** MOST25 Control Message Node Mode */
/* <Time> <Channel> <Dir> <SourceAdr> <DestAdr> <RType> <D0> <D1>...<D16> <State2> */
class Most25ControlMessageNodeMode : public Event
{
public:
    Most25ControlMessageNodeMode();
    virtual ~Most25ControlMessageNodeMode();

    /** Time */
    float time;

    /** Channel */
    uint16_t channel;

    /** Dir */
    enum class Dir {
        Rx,
        Tx
    };

    Dir dir;

    /** SourceAdr */
    uint16_t sourceAdr;

    /** DestAdr */
    uint16_t destAdr;

    /** RType */
    uint8_t rType;

    /** Data */
    uint8_t data[17];

    /** State2 */
    uint16_t state2;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static Most25ControlMessageNodeMode * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
