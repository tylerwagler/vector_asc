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

#include "platform.h"

#include <array>

#include "Event.h"

namespace Vector {
namespace ASC {

/**
 * FlexRay Status Event ("SE")
 *
 * FlexRay Message received or transmitted on a FlexRay channel.
 */
class FlexRayStatus : public Event
{
public:
    FlexRayStatus();

    /** Timestamp */
    double time;

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

    /** CC-Type. */
    uint32_t ccType;

    /** Sync-State */
    uint32_t syncState;

    /** CC-Data[2] */
    std::array<uint32_t, 2> ccData;

    /** Symbol */
    uint32_t symbol;

    /** WakeUp State */
    uint32_t wakeUpState;

    /** Spy flag */
    bool spyFlag;

    /** @copydoc Event::parse() */
    static FlexRayStatus * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
