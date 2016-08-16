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

#include "Event.h"
#include "MostSymbols.h"

#include "vector_asc_export.h"

namespace Vector {
namespace ASC {

/**
 * MOST Special Register Event
 *
 * This event reports the change of an important transceiver register like node position or node ad-
 * dress. It can occur spontaneous or as result of a read/write operation (see 0).
 * Directly after measurement start the current values of the special registers are reported even if they
 * have not changed.
 */
class VECTOR_ASC_EXPORT MostSpecialRegister final : public Event
{
public:
    MostSpecialRegister();

    /** @copydoc MostTime */
    MostTime time;

    /** @copydoc MostChannel */
    MostChannel channel;

    /** @copydoc MostRegSubType */
    MostRegSubType regSubType;

    /** @copydoc MostRegId */
    MostRegId regId;

    /** @copydoc MostRegValue */
    MostRegValue regValue;

    /** @copydoc Event::read() */
    static MostSpecialRegister * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
