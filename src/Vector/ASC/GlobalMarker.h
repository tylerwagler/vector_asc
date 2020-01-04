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
#include <Vector/ASC/CanSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * Global marker event
 *
 * A global marker event that is written if global marker is defined for a time stamp or for another event. If a
 * global marker event is assigned to another event (set in Trace Window) it has to be written before that
 * event. Global marker events can be written only during the export from Trace window.
 */
struct VECTOR_ASC_EXPORT GlobalMarker final : Event {
    GlobalMarker() : Event(EventType::GlobalMarker) {}

    /** @copydoc Time */
    Time time {0.0};

    /** the type of the commented event */
    uint32_t type {0};

    /** background color of the marker group */
    uint32_t backgroundColor {0};

    /** foreground color of the marker group */
    uint32_t foregroundColor {0};

    /** defines whether the marker can be moved */
    bool relocatable {true};

    /** the name of the marker group */
    std::string groupName {};

    /** the name of the marker */
    std::string markerName {};

    /** marker description */
    std::string description {};

    /** @copydoc Event::read() */
    static GlobalMarker * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
