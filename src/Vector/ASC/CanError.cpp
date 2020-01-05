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
#include <Vector/ASC/CanError.h>
#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

CanError * CanError::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "CAN" REGEX_WS  REGEX_Channel REGEX_WS "Status:" REGEX_ws REGEX_Error REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * canError = new CanError;
        canError->time = std::stod(match[1]);
        canError->channel = std::stoul(match[2]);
        std::string errorStr = match[3];
        size_t rxErrPos = errorStr.find(" RxErr: ");
        if (rxErrPos != std::string::npos) {
            canError->rxErr = std::stoul(errorStr.substr(rxErrPos + 8));
            errorStr.erase(rxErrPos);
        }
        size_t txErrPos = errorStr.find(" TxErr: ");
        if (txErrPos != std::string::npos) {
            canError->txErr = std::stoul(errorStr.substr(txErrPos + 8));
            errorStr.erase(txErrPos);
        }
        size_t minusPos = errorStr.find(" -");
        if (minusPos != std::string::npos)
            errorStr.erase(minusPos);
        if (errorStr == "chip status busoff")
            canError->error = Error::ChipStatusBusoff;
        else if (errorStr == "chip status error passive")
            canError->error = Error::ChipStatusErrorPassive;
        else if (errorStr == "chip status error active")
            canError->error = Error::ChipStatusErrorActive;
        else if (errorStr == "rx queue overrun")
            canError->error = Error::RxQueueOverrun;
        else if (errorStr == "chip status warning level")
            canError->error = Error::ChipStatusWarningLevel;
        else if (errorStr == "hardware interface disconnected")
            canError->error = Error::HardwareInterfaceDisconnected;
        else
            canError->error = Error::Unknown;
        return canError;
    }

    return nullptr;
}

void CanError::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);

    if (file.version >= File::Version::Ver_8_0) {
        /* "format: "CAN %d Status: " */
        stream
                << " CAN " << std::dec << (int16_t) channel
                << " Status: ";
    } else {
        /* "format: "CAN %d Status:" */
        stream
                << " CAN " << std::dec << (int16_t) channel
                << " Status:";
    }

    switch (error) {
    case Error::Unknown:
        break;
    case Error::ChipStatusBusoff:
        /* format: "chip status busoff" */
        stream << "chip status busoff";
        break;
    case Error::ChipStatusErrorPassive:
        /* format: "chip status error passive" */
        stream << "chip status error passive";
        break;
    case Error::ChipStatusErrorActive:
        /* format: "chip status error active" */
        stream << "chip status error active";
        break;
    case Error::RxQueueOverrun:
        /* format: "rx queue overrun" */
        stream << "rx queue overrun";
        break;
    case Error::ChipStatusWarningLevel:
        /* format: "chip status warning level" */
        stream << "chip status warning level";
        break;
    case Error::HardwareInterfaceDisconnected:
        /* format: "hardware interface disconnected" */
        stream << "hardware interface disconnected";
        break;
    }

    /* format: "%s - TxErr: %d RxErr: %d" */
    if ((txErr > 0) || (rxErr > 0)) {
        stream
                << " -"
                << " TxErr: " << std::dec << (uint16_t) txErr
                << " RxErr: " << std::dec << (uint16_t) rxErr;
    }

    stream << endl;
}

}
}
