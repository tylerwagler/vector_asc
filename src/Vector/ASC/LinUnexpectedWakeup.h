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

/** LIN Unexpected wakeup */
/* <Time> <Channel> Unexpected wakeup: approx. <Width> us SOF = <start of frame> BR = <baudrate> */
/* <Time> <Channel> Unexpected wakeup: Signal = <WakeupByte> SOF = <start of frame> BR =
 * <baudrate> */
class LinUnexpectedWakeup : public Event
{
public:
    LinUnexpectedWakeup();
    virtual ~LinUnexpectedWakeup();

    /** Time */
    float time;

    /** Channel */
    std::string channel;

    /** Width */
    uint16_t width;

    /** start of frame (SOF) */
    float startOfFrame;

    /** baudrate (BR) */
    uint16_t baudrate;


    /** WakeupByte */
    uint8_t wakeupByte;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static LinUnexpectedWakeup * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
