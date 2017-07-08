# dependencies
include(GenerateExportHeader)

# search paths
include_directories(
    ${FLEX_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})

# sources/headers
set(source_files
    AfdxPacket.cpp
    BeginTriggerblock.cpp
    CanBusStatistics.cpp
    CanCommon.cpp
    CanError.cpp
    CanErrorFrame.cpp
    CanExtendedMessage.cpp
    CanFdErrorFrame.cpp
    CanFdExtendedMessage.cpp
    CanFdMessage.cpp
    CanMessage.cpp
    CanOverloadFrame.cpp
    CanRemoteFrame.cpp
    Comment.cpp
    DiagRequest.cpp
    EndTriggerblock.cpp
    EnvironmentVariables.cpp
    EthernetCommon.cpp
    EthernetPacket.cpp
    EthernetRxError.cpp
    EthernetStatus.cpp
    Event.cpp
    File.cpp
    FileBaseTimestamps.cpp
    FileComment.cpp
    FileDate.cpp
    FileInternalEventsLogged.cpp
    FileSplitInformation.cpp
    FileVersion.cpp
    FlexRayCommon.cpp
    FlexRayError.cpp
    FlexRayMessage.cpp
    FlexRayOldMessage.cpp
    FlexRayOldStartCycle.cpp
    FlexRayStartCycle.cpp
    FlexRayStatus.cpp
    GlobalMarker.cpp
    Gps.cpp
    KLineByte.cpp
    KLineCommon.cpp
    KLineMessage.cpp
    LinBaudrate.cpp
    LinChecksumError.cpp
    LinChecksumInfo.cpp
    LinCommon.cpp
    LinDisturbance.cpp
    LinDlcInfo.cpp
    LinDominantSignal.cpp
    LinEventTriggeredFrameInfo.cpp
    LinMessage.cpp
    LinReceiveError.cpp
    LinSchedulerModeChange.cpp
    LinShortOrSlowResponse.cpp
    LinSlaveTimeout.cpp
    LinSleepMode.cpp
    LinSpike.cpp
    LinStatisticInfo.cpp
    LinSyncError.cpp
    LinTransmissionError.cpp
    LinUnexpectedWakeup.cpp
    LinWakeupFrame.cpp
    LogDirectStart.cpp
    LogDirectStop.cpp
    LogTrigger.cpp
    MacroSignal.cpp
    Most150AllocTable.cpp
    Most150ControlMessage.cpp
    Most150ControlMessageFragment.cpp
    Most150Packet.cpp
    Most150PacketFragment.cpp
    Most25AllocTable.cpp
    Most25ControlMessageNodeMode.cpp
    Most25ControlMessageSpyMode.cpp
    Most25Packet.cpp
    Most50ControlMessage.cpp
    Most50Packet.cpp
    MostCommon.cpp
    MostCommonRegister.cpp
    MostDataLost.cpp
    MostEcl.cpp
    MostEthernetPacket.cpp
    MostEthernetPacketFragment.cpp
    MostHwMode.cpp
    MostLightLock.cpp
    MostNetState.cpp
    MostSpecialRegister.cpp
    MostStatistic.cpp
    MostStatisticExtended.cpp
    MostStress.cpp
    MostSystem.cpp
    MostTrigger.cpp
    MostTxLight.cpp
    StartOfMeasurement.cpp
    SystemVariables.cpp
    TpConsecutiveFrame.cpp
    TpDiagCommon.cpp
    TpFirstFrame.cpp
    TpFlowControlFrame.cpp
    TpSingleFrame.cpp
    Unknown.cpp)
set(public_header_files
    AfdxPacket.h
    BeginTriggerblock.h
    CanBusStatistics.h
    CanError.h
    CanErrorFrame.h
    CanExtendedMessage.h
    CanFdErrorFrame.h
    CanFdExtendedMessage.h
    CanFdMessage.h
    CanMessage.h
    CanOverloadFrame.h
    CanRemoteFrame.h
    CanSymbols.h
    Comment.h
    DiagRequest.h
    EndTriggerblock.h
    EnvironmentVariables.h
    EthernetPacket.h
    EthernetRxError.h
    EthernetStatus.h
    EthernetSymbols.h
    Event.h
    File.h
    FileBaseTimestamps.h
    FileComment.h
    FileDate.h
    FileInternalEventsLogged.h
    FileSplitInformation.h
    FileVersion.h
    FlexRayError.h
    FlexRayMessage.h
    FlexRayOldMessage.h
    FlexRayOldStartCycle.h
    FlexRayStartCycle.h
    FlexRayStatus.h
    FlexRaySymbols.h
    GlobalMarker.h
    Gps.h
    KLineByte.h
    KLineMessage.h
    KLineSymbols.h
    LinBaudrate.h
    LinChecksumError.h
    LinChecksumInfo.h
    LinDisturbance.h
    LinDlcInfo.h
    LinDominantSignal.h
    LinEventTriggeredFrameInfo.h
    LinMessage.h
    LinReceiveError.h
    LinSchedulerModeChange.h
    LinShortOrSlowResponse.h
    LinSlaveTimeout.h
    LinSleepMode.h
    LinSpike.h
    LinStatisticInfo.h
    LinSymbols.h
    LinSyncError.h
    LinTransmissionError.h
    LinUnexpectedWakeup.h
    LinWakeupFrame.h
    LogDirectStart.h
    LogDirectStop.h
    LogTrigger.h
    MacroSignal.h
    Most150AllocTable.h
    Most150ControlMessage.h
    Most150ControlMessageFragment.h
    Most150PacketFragment.h
    Most150Packet.h
    Most25AllocTable.h
    Most25ControlMessageNodeMode.h
    Most25ControlMessageSpyMode.h
    Most25Packet.h
    Most50ControlMessage.h
    Most50Packet.h
    MostCommonRegister.h
    MostDataLost.h
    MostEcl.h
    MostEthernetPacketFragment.h
    MostEthernetPacket.h
    MostHwMode.h
    MostLightLock.h
    MostNetState.h
    MostSpecialRegister.h
    MostStatistic.h
    MostStatisticExtended.h
    MostStress.h
    MostSymbols.h
    MostSystem.h
    MostTrigger.h
    MostTxLight.h
    platform.h
    StartOfMeasurement.h
    SystemVariables.h
    TpConsecutiveFrame.h
    TpDiagSymbols.h
    TpFirstFrame.h
    TpFlowControlFrame.h
    TpSingleFrame.h
    Unknown.h)
set(private_header_files
    CanCommon.h
    CanSymbolsRegEx.h
    EthernetCommon.h
    EthernetSymbolsRegEx.h
    FlexRayCommon.h
    FlexRaySymbolsRegEx.h
    KLineCommon.h
    KLineSymbolsRegEx.h
    LinCommon.h
    LinSymbolsRegEx.h
    MostCommon.h
    MostSymbolsRegEx.h
    TpDiagCommon.h
    TpDiagSymbolsRegEx.h)
set(info_files
    Lexer.l)

# generated files
configure_file(config.h.in config.h)
configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

# compiler/linker settings
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
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

# targets
if(WIN32)
    flex_target(Lexer Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp
        COMPILE_FLAGS --wincompat)
else()
    flex_target(Lexer Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp)
endif()
add_library(${PROJECT_NAME} SHARED
    ${source_files} ${public_header_files} ${private_header_files} ${info_files}
    ${FLEX_Lexer_OUTPUTS})
generate_export_header(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN 1)
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
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
        ${CMAKE_CURRENT_BINARY_DIR}/vector_asc_export.h
        ${public_header_files}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Vector/ASC)

# sub directories
add_subdirectory(docs)
add_subdirectory(tests)
