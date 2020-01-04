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
 * MOST HW Mode Event
 *
 * This event is fired when one or more HW state changes. HW states are the AllBypass bit (ABY of
 * OS8104), the Master/Slave selection (MTR of OS8104), the Control spy and the Asynchronous
 * spy. The event transports all states even if only a single state has changed. <HWModeMask> de-
 * notes which state differs regarding to the previous HW mode event.
 */
struct VECTOR_ASC_EXPORT MostHwMode final : Event {
    MostHwMode() : Event(EventType::MostHwMode) {}

    /** @copydoc MostTime */
    MostTime time {0.0};

    /** @copydoc MostChannel */
    MostChannel channel {0};

    /** @copydoc MostHwMode */
    MostHwModeType hwMode {0};

    /** @copydoc MostHwModeMask */
    MostHwModeMask hwModeMask {0};

    /** @copydoc Event::read() */
    static MostHwMode * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
