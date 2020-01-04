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

#include <Vector/ASC/platform.h>

#include <Vector/ASC/Event.h>
#include <Vector/ASC/LinSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

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
struct VECTOR_ASC_EXPORT LinStatisticInfo final : Event {
    LinStatisticInfo() : Event(EventType::LinStatisticInfo) {}

    /** @copydoc LinTime */
    LinTime time {0.0};

    /** @copydoc LinChannel */
    LinChannel channel {0};

    /** ChannelNum */
    uint16_t channelNum {0};

    /** BusLoad */
    double busLoad {0.0};

    /** Bursts total */
    uint32_t burstsTotal {0};

    /** Bursts overrun */
    uint32_t burstsOverrun {0};

    /** Frame sent */
    uint32_t framesSent {0};

    /** Frames received */
    uint32_t framesReceived {0};

    /** Frames unanswered */
    uint32_t framesUnanswered {0};

    /** @copydoc Event::read() */
    static LinStatisticInfo * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
