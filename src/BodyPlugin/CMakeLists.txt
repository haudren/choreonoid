
# @author Shin'ichiro Nakaoka

#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
#set_source_files_properties(SimulatorItem.cpp PROPERTIES COMPILE_FLAGS "-O0 -g")

set(sources
  BodyPlugin.cpp
  BodyItem.cpp
  WorldItem.cpp
  BodyMotionItem.cpp
  ZMPSeqItem.cpp
  MultiDeviceStateSeqItem.cpp
  SimulatorItem.cpp
  ControllerItem.cpp
  SimulationScriptItem.cpp
  AISTSimulatorItem.cpp
  GLVisionSimulatorItem.cpp
  SensorVisualizerItem.cpp
  BodyMotionEngine.cpp
  KinematicFaultChecker.cpp
  #FilterDialogs.cpp
  EditableSceneBody.cpp
  BodyBar.cpp
  LeggedBodyBar.cpp
  KinematicsBar.cpp
  SimulationBar.cpp
  LinkTreeWidget.cpp
  LinkSelectionView.cpp
  BodyLinkView.cpp
  JointSliderView.cpp
  JointStateView.cpp
  BodyStateView.cpp
  JointGraphView.cpp
  LinkGraphView.cpp
  HrpsysFileIO.cpp
  CollisionSeq.cpp
  CollisionSeqItem.cpp
  CollisionSeqEngine.cpp
  )

set(headers
  BodyItem.h
  WorldItem.h
  BodyMotionItem.h
  MultiDeviceStateSeqItem.cpp
  SimulatorItem.h
  SubSimulatorItem.h
  ControllerItem.h
  SimulationScriptItem.h
  SensorVisualizerItem.h
  KinematicFaultChecker.h
  BodyBar.h
  KinematicsBar.h
  SimulationBar.h
  LinkTreeWidget.h
  LinkSelectionView.h
  EditableSceneBody.h
  exportdecl.h
  gettext.h
  CollisionSeq.h
  CollisionSeqItem.h
  CollisionSeqEngine.h
  )

set(target CnoidBodyPlugin)

make_gettext_mofiles(${target} mofiles)

if(NOT QT5)
  QT4_WRAP_CPP(sources
    LinkTreeWidget.h
    OPTIONS "-DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED"
    )
  QT4_ADD_RESOURCES(RC_SRCS BodyPlugin.qrc)
else()
  QT5_ADD_RESOURCES(RC_SRCS BodyPlugin.qrc)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_cnoid_plugin(${target} SHARED ${sources} ${headers} ${mofiles} ${RC_SRCS})

if(QT5)
  qt5_use_modules(${target} Gui OpenGL Network)
endif()

set(boost_libraries ${Boost_REGEX_LIBRARY} ${Boost_IOSTREAMS_LIBRARY})
if(MSVC)
  set(boost_libraries ${boost_libraries} ${Boost_BZIP2_LIBRARY} ${Boost_ZLIB_LIBRARY})
endif()

target_link_libraries(${target} CnoidBase CnoidBody ${boost_libraries})
apply_common_setting_for_plugin(${target} "${headers}")

if(ENABLE_PYTHON)
  add_subdirectory(python)
endif()
