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

/** LIN Sync Error */
/* <Time> <Channel> SyncError <TimeInterval0>..<TimeInterval3> */
/* <Time> <Channel> SyncError <TimeInterval0>..<TimeInterval3> SOF = <start of frame> BR =
 * <baudrate> break = <SyncBreak> <SyncDel> */
class LinSyncError : public Event
{
public:
    LinSyncError();
    virtual ~LinSyncError();

    /** Time */
    float time;

    /** Channel */
    uint16_t channel;

    /** TimeInterval */
    uint8_t timeInterval[4];


    /** start of frame (SOF) */
    float startOfFrame;

    /** baudrate (BR) */
    uint16_t baudrate;

    /** SyncBreak */
    uint32_t syncBreak;

    /** SyncDel */
    uint32_t syncDel;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static LinSyncError * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
