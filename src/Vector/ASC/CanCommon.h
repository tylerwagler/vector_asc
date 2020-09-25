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

#include <ostream>
#include <string>
#include <vector>

#include <Vector/ASC/File.h>
#include <Vector/ASC/CanSymbols.h>

namespace Vector {
namespace ASC {

/** Windows endline (also on Linux) */
extern const std::string endl;

/**
 * Write data in output stream, either in hex or dec depending on file.base
 *
 * @param file reference to file to get numeric base
 * @param stream output stream
 * @param data data to write
 */
void writeData(const File & file, std::ostream & stream, const std::vector<uint8_t> & data);

/**
 * Write direction Rx/Tx/TxRq into output stream
 *
 * @param file reference to file
 * @param stream output stream
 * @param dir direction
 */
void writeDir(const File & file, std::ostream & stream, const Dir dir);

/**
 * Write timestamp (roughly strftime for Vector::ASC)
 *
 * @param file reference to file to get timestamp precision
 * @param stream output stream
 * @param time timestamp
 */
void writeTime(const File & file, std::ostream & stream, const Time & time);

/**
 * Read timestamp (roughly strptime for Vector::ASC)
 *
 * @param[in] wday weekday
 * @param[in] mon month
 * @param[in] mday day of month
 * @param[in] hour hour
 * @param[in] min minute
 * @param[in] sec second
 * @param[in] amFm "am", "fm", or nothing
 * @param[in] year year
 * @param[out] language contains detected language
 * @param[out] tm contains parsed date structure
 */
void readDate(const std::string & wday, const std::string & mon, const std::string & mday,
    const std::string & hour, const std::string & min, const std::string & sec, const std::string & amFm,
    const std::string & year,
    File::Language & language,
    tm & date);

/**
 * strftime modified for Vector::ASC
 *
 * @param file reference to file to get language
 * @param stream output stream
 * @param tm date structure
 */
void writeDate(const File & file, std::ostream & ostream, const struct tm & date);

}
}
