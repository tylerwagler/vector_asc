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

void writeTime(File & file, std::ostream & stream, Time & time)
{
    stream << std::right << std::setfill(' ') << std::setw(11) << std::setprecision(6) << std::fixed << time;
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

}
}
