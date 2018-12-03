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

#include <string>
#include <vector>

#include <Vector/ASC/File.h>
#include <Vector/ASC/CanSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/* force Linux to use Windows line ending */
static const char endl[] = "\r\n";

/**
 * Write data in output stream, either in hex or dec depending on file.base
 *
 * @param file reference to file to get numeric base
 * @param stream output stream
 * @param data data to write
 */
void writeData(File & file, std::ostream & stream, std::vector<uint8_t> & data);

/**
 * Write direction Rx/Tx/TxRq into output stream
 *
 * @param file reference to file
 * @param stream output stream
 * @param dir direction
 */
void writeDir(File & file, std::ostream & stream, Dir dir);

/**
 * Write timestamp (roughly strftime for Vector::ASC)
 *
 * @param file reference to file to get timestamp precision
 * @param stream output stream
 * @param time timestamp
 */
void writeTime(File & file, std::ostream & stream, Time & time);

/**
 * Read timestamp (roughly strptime for Vector::ASC)
 *
 * @param wday weekday
 * @param mon month
 * @param mday day of month
 * @param hour hour
 * @param min minute
 * @param sec second
 * @param amFm "am", "fm", or nothing
 * @param year year
 * @param language contains detected language
 * @param tm contains parsed date structure
 */
void readDate(
        std::string wday, std::string mon, std::string mday,
        std::string hour, std::string min, std::string sec, std::string amFm,
        std::string year,
        File::Language & language,
        struct tm & date);

/**
 * strftime modified for Vector::ASC
 *
 * @param file reference to file to get language
 * @param stream output stream
 * @param tm date structure
 */
void writeDate(File & file, std::ostream & ostream, struct tm & date);

}
}
