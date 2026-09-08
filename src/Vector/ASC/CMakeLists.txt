# dependencies
include(GenerateExportHeader)

# targets
# Honor BUILD_SHARED_LIBS instead of forcing SHARED, so consumers that build static
# (e.g. openSYDE sets BUILD_SHARED_LIBS OFF) statically link this library.
add_library(${PROJECT_NAME} "")

# search paths
include_directories(
    ${FLEX_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src)

# sources/headers
target_sources(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/AfdxPacket.h
        ${CMAKE_CURRENT_SOURCE_DIR}/BeginTriggerblock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanBusStatistics.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanErrorFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanExtendedMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdErrorFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdExtendedMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanOverloadFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanRemoteFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanSymbols.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Comment.h
        ${CMAKE_CURRENT_SOURCE_DIR}/DiagRequest.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EndTriggerblock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentVariables.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetPacket.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetRxError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetStatus.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetSymbols.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Event.h
        ${CMAKE_CURRENT_SOURCE_DIR}/File.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FileBaseTimestamps.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FileComment.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FileDate.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FileInternalEventsLogged.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FileSplitInformation.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FileVersion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayOldMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayOldStartCycle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayStartCycle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayStatus.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRaySymbols.h
        ${CMAKE_CURRENT_SOURCE_DIR}/GlobalMarker.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Gps.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KLineByte.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KLineMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KLineSymbols.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinBaudrate.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinChecksumError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinChecksumInfo.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinDisturbance.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinDlcInfo.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinDominantSignal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinEventTriggeredFrameInfo.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinReceiveError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSchedulerModeChange.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinShortOrSlowResponse.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSlaveTimeout.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSleepMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSpike.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinStatisticInfo.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSymbols.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSyncError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinTransmissionError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinUnexpectedWakeup.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinWakeupFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LogDirectStart.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LogDirectStop.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LogTrigger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MacroSignal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150AllocTable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150ControlMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150ControlMessageFragment.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150PacketFragment.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150Packet.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most25AllocTable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most25ControlMessageNodeMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most25ControlMessageSpyMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most25Packet.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most50ControlMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Most50Packet.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostCommonRegister.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostDataLost.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostEcl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostEthernetPacketFragment.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostEthernetPacket.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostHwMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostLightLock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostNetState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostSpecialRegister.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostStatistic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostStatisticExtended.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostStress.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostSymbols.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostTrigger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostTxLight.h
        ${CMAKE_CURRENT_SOURCE_DIR}/platform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/StartOfMeasurement.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SystemVariables.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TpConsecutiveFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TpDiagSymbols.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TpFirstFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TpFlowControlFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TpSingleFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Unknown.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/CanCommon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanSymbolsRegEx.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetCommon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetSymbolsRegEx.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayCommon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRaySymbolsRegEx.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KLineCommon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KLineSymbolsRegEx.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinCommon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSymbolsRegEx.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostCommon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MostSymbolsRegEx.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TpDiagCommon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TpDiagSymbolsRegEx.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/AfdxPacket.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BeginTriggerblock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanBusStatistics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanCommon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanErrorFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanExtendedMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdErrorFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdExtendedMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanOverloadFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanRemoteFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Comment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DiagRequest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EndTriggerblock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentVariables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetCommon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetPacket.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetRxError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EthernetStatus.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/File.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileBaseTimestamps.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileComment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileDate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileInternalEventsLogged.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileSplitInformation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileVersion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayCommon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayOldMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayOldStartCycle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayStartCycle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FlexRayStatus.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GlobalMarker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gps.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/KLineByte.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/KLineCommon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/KLineMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinBaudrate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinChecksumError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinChecksumInfo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinCommon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinDisturbance.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinDlcInfo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinDominantSignal.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinEventTriggeredFrameInfo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinReceiveError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSchedulerModeChange.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinShortOrSlowResponse.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSlaveTimeout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSleepMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSpike.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinStatisticInfo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinSyncError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinTransmissionError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinUnexpectedWakeup.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinWakeupFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LogDirectStart.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LogDirectStop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LogTrigger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MacroSignal.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150AllocTable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150ControlMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150ControlMessageFragment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150Packet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most150PacketFragment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most25AllocTable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most25ControlMessageNodeMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most25ControlMessageSpyMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most25Packet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most50ControlMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Most50Packet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostCommon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostCommonRegister.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostDataLost.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostEcl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostEthernetPacket.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostEthernetPacketFragment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostHwMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostLightLock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostNetState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostSpecialRegister.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostStatistic.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostStatisticExtended.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostStress.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostTrigger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MostTxLight.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StartOfMeasurement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SystemVariables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TpConsecutiveFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TpDiagCommon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TpFirstFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TpFlowControlFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TpSingleFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Unknown.cpp
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp)

# generated files
configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
generate_export_header(${PROJECT_NAME})
if(WIN32)
    flex_target(Lexer Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp
        COMPILE_FLAGS --wincompat)
else()
    flex_target(Lexer Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp)
endif()

# compiler/linker settings
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_VISIBILITY_PRESET "hidden"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION}
    VISIBILITY_INLINES_HIDDEN 1)
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-D_FORTIFY_SOURCE=2)
    #add_definitions(-fPIE -pie)
    add_definitions(-Wl,-z,relro,-z,now)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9)
        add_definitions(-fstack-protector-strong)
    endif()
    if(OPTION_USE_GCOV_LCOV)
        add_definitions(-g -O0 -fprofile-arcs -ftest-coverage)
    endif()
endif()
target_link_libraries(${PROJECT_NAME}
    ${ZLIB_LIBRARIES})
if(OPTION_USE_GCOV_LCOV)
    target_link_libraries(${PROJECT_NAME} gcov)
endif()

# install
install(
    TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/vector_asc_export.h
        $<TARGET_PROPERTY:${PROJECT_NAME},INTERFACE_SOURCES>
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Vector/ASC)

# sub directories
add_subdirectory(docs)
add_subdirectory(tests)
