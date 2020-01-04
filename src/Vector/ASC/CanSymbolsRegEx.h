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

/** CAN, Log & Trigger Symbols */

#pragma once

#include <Vector/ASC/platform.h>

namespace Vector {
namespace ASC {

/* Format Symbols */
#define REGEX_STOL "^[[:blank:]]*"
#define REGEX_ENDL "[[:blank:]]*[\r\n]*$"
#define REGEX_WS "[[:blank:]]+"
#define REGEX_ws "[[:blank:]]*"

/* CAN, Log & Trigger Symbols */
#define REGEX_Time "([[:digit:].]{3,})"
#define REGEX_Channel "([[:digit:]]{1,5})"
#define REGEX_IDnum "([[:xdigit:]]{1,14})"
// IDsym @todo
#define REGEX_ID REGEX_IDnum
#define REGEX_Dir "(Rx|Tx|TxRq)"
#define REGEX_DLC "([[:xdigit:]]{1,2})"
#define REGEX_MessageFlags "(TE|WU|XX)"
#define REGEX_StatNumber "([[:digit:]]{1,10})"
#define REGEX_StatPercent "([[:digit:].]{3,6})"
#define REGEX_PreTrigger "([[:digit:]]{1,10})"
#define REGEX_PostTrigger "([[:digit:]]{1,10})"
#define REGEX_Error "(.+?)"
#define REGEX_Dx "[[:xdigit:]]{1,3}"
#define REGEX_WeekDay "(Mon|Tue|Wed|Thu|Fri|Sat|Sun|Mon|Die|Mit|Don|Fre|Sam|Son)"
#define REGEX_Month "(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec|Jan|Feb|M.r|Apr|Mai|Jun|Jul|Aug|Sep|Okt|Nov|Dez)"
#define REGEX_Date "([[:digit:]]{1,2})"
#define REGEX_FullTime "([[:digit:]]{2}):([[:digit:]]{2}):([[:digit:]]{2})( am| pm)?"
#define REGEX_Year "([[:digit:]]{4})"
#define REGEX_svtype "([12345])"
#define REGEX_MessageDuration "([[:digit:]]+)"
#define REGEX_MessageLength "([[:digit:]]+)"
#define REGEX_BRS "([01])"
#define REGEX_ESI "([01])"
#define REGEX_DataLength "([[:digit:]]{1,3})"
#define REGEX_BitTimingConfArb "([[:xdigit:]]{8})"
#define REGEX_BitTimingConfData "([[:xdigit:]]{8})"

}
}
