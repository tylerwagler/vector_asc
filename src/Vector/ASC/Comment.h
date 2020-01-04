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

#include <string>

#include <Vector/ASC/Event.h>
#include <Vector/ASC/CanSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * Comment Event
 *
 * A comment event that is written before another event that was commented in Trace Window. Commenting events is
 * supported only in Trace Window, so this event can be written only during the export from Trace window.
 */
struct VECTOR_ASC_EXPORT Comment final : Event {
    Comment() : Event(EventType::Comment) {}

    /** @copydoc Time */
    Time time {0.0};

    /** the type of the commented event */
    uint32_t type {0};

    /** the text of the comment */
    std::string commentText {};

    /** @copydoc Event::read() */
    static Comment * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
