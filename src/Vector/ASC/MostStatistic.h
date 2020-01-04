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
#include <Vector/ASC/MostSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * MOST Statistic Event
 *
 * The event transports common network statistics. These are the number of Control messages (Fr),
 * number of signal state transition (Lt) events and number of packets (Pk) since the last Statistic
 * event. Bl denotes the fill level of the interface’s event queue (Optolyzer G1 only).
 *
 * Usually the event is not visible in a trace window.
 */
struct VECTOR_ASC_EXPORT MostStatistic final : Event {
    MostStatistic() : Event(EventType::MostStatistic) {}

    /** @copydoc MostTime */
    MostTime time {0.0};

    /** @copydoc MostChannel */
    MostChannel channel {0};

    /** number of Control messages */
    MostStatVal fr {0};

    /** number of signal state transition events */
    MostStatVal lt {0};

    /** fill level of the interface’s event queue (Optolyzer G1 only) */
    MostStatVal bl {0};

    /** number of packets */
    MostStatVal pk {0};

    /** @copydoc Event::read() */
    static MostStatistic * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
