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

#include <iomanip>
#include "CanCommon.h"

namespace Vector {
namespace ASC {

void writeData(File & file, std::ostream & stream, std::vector<uint8_t> & data)
{
    for(uint8_t d: data) {
        switch(file.base) {
        case 10:
            stream << ' ' << std::right
                   << std::setfill(' ') << std::setw(3)
                   << std::dec << (uint16_t) d;
            break;
        case 16:
            stream << ' ' << std::right
                   << std::setfill('0') << std::setw(2)
                   << std::hex << (uint16_t) d;
            break;
        }
    }
}

void writeDir(File & file, std::ostream & stream, Dir dir)
{
    switch(dir) {
    case Dir::Rx:
        /* format: "Rx" */
        stream << "Rx";
        break;
    case Dir::Tx:
        /* format: "Tx" */
        stream << "Tx";
        break;
    case Dir::TxRq:
        /* format: "TxRq" */
        stream << "TxRq";
        break;
    }
}

void writeTime(File & file, std::ostream & stream, Time & time)
{
    stream
            << std::right << std::setfill(' ')
            << std::setw(5 + file.timestampPrecision)
            << std::setprecision(file.timestampPrecision)
            << std::fixed << time;
}

}
}
