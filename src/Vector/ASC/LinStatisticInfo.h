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
#include "LinSymbols.h"

namespace Vector {
namespace ASC {

/**
 * LIN Statistic Info
 *
 * This info event transports bus statistics. (Bus load [in range 0..1], obsolete value, obsolete value,
 * transmitted frames, received frames, transmission errors )
 *
 * IMPORTANT: This event is generated up to CANoe/CANalyzer 5.2 only.
 */
class LinStatisticInfo : public Event
{
public:
    LinStatisticInfo();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** ChannelNum */
    uint16_t channelNum;

    /** BusLoad */
    double busLoad;

    /** Bursts total */
    uint32_t burstsTotal;

    /** Bursts overrun */
    uint32_t burstsOverrun;

    /** Frame sent */
    uint32_t framesSent;

    /** Frames received */
    uint32_t framesReceived;

    /** Frames unanswered */
    uint32_t framesUnanswered;

    /** @copydoc Event::parse() */
    static LinStatisticInfo * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
