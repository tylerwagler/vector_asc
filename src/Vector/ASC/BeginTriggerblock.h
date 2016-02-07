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

#include <ctime>

#include "Event.h"

#include "vector_asc_export.h"

namespace Vector {
namespace ASC {

/**
 * Begin Triggerblock Event
 *
 * An event that is written when a trigger block begins.
 */
class VECTOR_ASC_EXPORT BeginTriggerblock : public Event
{
public:
    BeginTriggerblock();

    /** date/time */
    tm date;

    /** language (only parsed, write works via File::language) */
    File::Language language;

    /** @copydoc Event::parse() */
    static BeginTriggerblock * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
