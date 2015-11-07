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

/** FlexRay Message Event (Old Format) */
/* <Time> <Channel> <Typ> <Id> <Cycle> <NM> <Sync> <HeaderCRC> <SymbolicName> <DLC> <D0> <D1>...<D64> x<FrameState> x<HeaderBitMask> */
class FlexRayOldMessageEvent : public Event
{
public:
    FlexRayOldMessageEvent();
    virtual ~FlexRayOldMessageEvent();

    /** Time */
    float time;

    /** Channel */
    std::string channel;

    /** Typ */
    std::string typ;

    /** Id */
    uint16_t id;

    /** Cycle */
    uint8_t cycle;

    /** NM */
    bool nm;

    /** Sync */
    bool sync;

    /** HeaderCRC */
    uint16_t headerCrc;

    /** SymbolicName */
    std::string symbolicName;

    /** DLC */
    uint8_t dlc;

    /** Data */
    uint8_t data[255];

    /** FrameState */
    uint16_t frameState;

    /** HeaderBitMask */
    uint8_t headerBitMask;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static FlexRayOldMessageEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
