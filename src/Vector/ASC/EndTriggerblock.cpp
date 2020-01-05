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

#include <regex>

#include <Vector/ASC/CanCommon.h>
#include <Vector/ASC/CanSymbolsRegEx.h>
#include <Vector/ASC/EndTriggerblock.h>

namespace Vector {
namespace ASC {

EndTriggerblock * EndTriggerblock::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL "End TriggerBlock" REGEX_ENDL);
    if (std::regex_match(line, regex)) {
        auto * endTriggerblock = new EndTriggerblock;
        return endTriggerblock;
    }

    return nullptr;
}

void EndTriggerblock::write(File & /*file*/, std::ostream & stream) {
    /* format: "End TriggerBlock" */
    stream << "End TriggerBlock";

    stream << endl;
}

}
}
