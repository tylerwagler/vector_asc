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

#include <vector>

#include <Vector/ASC/Event.h>
#include <Vector/ASC/MostSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * MOST25 Alloc Table
 *
 * The event transports the current Allocation Table of the connected hardware interface.
 *
 * The label of a synchronous connection can be distributed over several bytes in the Allocation Ta-
 * ble. Each byte <Dx> contains a value that specifies the identification number of the label it belongs
 * to. If the device is a timing master, the MSB of the byte value is used to indicate if the label is in
 * use or not, otherwise the MSB should be ignored. The label number thus can be determined by byte
 * value & 0x7F. If the resulting label number is 0x70, the byte is not used for any label.
 */
struct VECTOR_ASC_EXPORT Most25AllocTable final : Event {
    Most25AllocTable() : Event(EventType::Most25AllocTable) {}

    /** @copydoc MostTime */
    MostTime time {0.0};

    /** @copydoc MostChannel */
    MostChannel channel {0};

    /** @copydoc MostAllocTableSize */
    MostAllocTableSize allocTableSize {0};

    /** @copydoc MostDxAt */
    std::vector<MostDxAt> data {};

    /** @copydoc Event::read() */
    static Most25AllocTable * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
