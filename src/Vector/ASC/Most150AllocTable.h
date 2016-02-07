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

#include <vector>

#include "Event.h"
#include "MostSymbols.h"

#include "vector_asc_export.h"

namespace Vector {
namespace ASC {

/**
 * MOST50/150 Allocation Table
 *
 * The event transports the current state and changes of the MOST50/MOST150 Allocation Table.
 */
class VECTOR_ASC_EXPORT Most150AllocTable : public Event
{
public:
    Most150AllocTable();

    /** @copydoc MostTime */
    MostTime time;

    /** @copydoc MostChannel */
    MostChannel channel;

    /** @copydoc MostAt150EventModeFlags */
    MostAt150EventModeFlags at150EventModeFlags;

    /** @copydoc MostFreeBytes */
    MostFreeBytes freeBytes;

    /** @copydoc MostAt150Size */
    MostAt150Size at150Size;

    /** @copydoc MostWx */
    std::vector<MostWx> wordData;

    /** @copydoc Event::parse() */
    static Most150AllocTable * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
