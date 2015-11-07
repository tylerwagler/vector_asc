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

/** FlexRay Start Cycle Event ("SCE") */
class FlexRayStartCycleEvent : public Event
{
public:
    FlexRayStartCycleEvent();
    virtual ~FlexRayStartCycleEvent();

    /** Timestamp */
    float time;

    /** Clusternr. */
    uint32_t clusterNr;

    /** Client-ID */
    uint32_t clientId;

    /** Channelnr. */
    uint32_t channelNr;

    /** Channel mask */
    uint32_t channelMask;

    /** Cycle no. */
    uint32_t cycleNo;

    /** Direction */
    std::string direction;

    /** CC-Type. */
    uint32_t ccType;

    /** CC-Data[5] */
    uint32_t ccData[5];

    /** NM_Vect_L */
    uint32_t nmVectL;

    /** NM_Vect[n] */
    uint32_t nmVect[256];

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static FlexRayStartCycleEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
