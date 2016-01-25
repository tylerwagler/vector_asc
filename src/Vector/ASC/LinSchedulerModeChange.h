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
 * LIN Scheduler Mode Change
 *
 * This info event is only displayed when a Master is simulated and a frame header of a new schedule
 * table is transmitted for the first time. This info event may appear on starting a measurement.
 */
class LinSchedulerModeChange : public Event
{
public:
    LinSchedulerModeChange();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinScheduleTableIndex */
    LinScheduleTableIndex priorSchedulerMode;

    /** @copydoc LinScheduleTableIndex */
    LinScheduleTableIndex nextSchedulerMode;

    /** @copydoc Event::parse() */
    static LinSchedulerModeChange * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
