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

#include <vector>
#include "Event.h"
#include "TpDiagSymbols.h"

namespace Vector {
namespace ASC {

/** TP Single Frame */
class TpSingleFrame : public Event
{
public:
    TpSingleFrame();
    virtual ~TpSingleFrame();

    /** @copydoc TpDiagCanChannel */
    TpDiagCanChannel canChannel;

    /** @copydoc TpDiagConnectionId */
    TpDiagConnectionId connectionId;

    /** @copydoc TpDiagType */
    TpDiagType type;

    /** @copydoc TpDiagSource */
    TpDiagSource source;

    /** @copydoc TpDiagDestination */
    TpDiagDestination destination;

    /** @copydoc TpDiagLength */
    TpDiagLength length;

    /** @copydoc TpDiagTransportedBytes */
    std::vector<TpDiagTransportedBytes> transportedBytes;

    /** @copydoc Event::parse() */
    static TpSingleFrame * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
