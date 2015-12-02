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

#include <string>
#include <vector>
#include "File.h"
#include "CanSymbols.h"

namespace Vector {
namespace ASC {

/* force Linux to use Windows line ending */
static const char endl[] = "\r\n";

void writeData(File & file, std::ostream & stream, std::vector<uint8_t> & data);

void writeDir(File & file, std::ostream & stream, Dir dir);

void writeTime(File & file, std::ostream & stream, Time & time);

}
}
