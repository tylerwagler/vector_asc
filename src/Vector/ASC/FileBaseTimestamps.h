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

/** File Base Timestamps */
class VECTOR_ASC_EXPORT FileBaseTimestamps final : public Event
{
public:
    FileBaseTimestamps();

    /** Events can either be recorder in hexadecimal or decimal mode. */
    File::Base base;

    /** Timestamps are written absolute or relative to the preceding event. */
    File::Timestamps timestamps;

    /** @copydoc Event::read() */
    static FileBaseTimestamps * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
