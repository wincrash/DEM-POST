cmake_minimum_required(VERSION 2.8)

project(DEM-POST)


FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

find_package(HDF5)
include_directories(${HDF5_INCLUDE_DIR})



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(H5Parser
    src/H5Parser/DEMOutput.cxx
    src/H5Parser/DEMOutput.h

    src/H5Parser/Point.cxx
    src/H5Parser/Point.h

    src/H5Parser/CSVRow.cxx
    src/H5Parser/CSVRow.h
    src/H5Parser/ParsingParameters.cxx
    src/H5Parser/ParsingParameters.h
    src/H5Parser/PorocityInBox.cxx
    src/H5Parser/PorocityInBox.h
    src/H5Parser/IndividualParticles.cxx
    src/H5Parser/IndividualParticles.h
    src/H5Parser/ACalculations.cxx
    src/H5Parser/ACalculations.h
    src/H5Parser/InformationOnLine.h
    src/H5Parser/InformationOnLine.cxx
    src/H5Parser/SpecForceTIRE.cxx
    src/H5Parser/SpecForceTIRE.h
    src/H5Parser/MeshCell.cxx
    src/H5Parser/MeshCell.h
    src/H5Parser/ContactInformation.cxx
    src/H5Parser/ContactInformation.h
    src/H5Parser/BondGenerator.cxx
    src/H5Parser/BondGenerator.h
    src/H5Parser/Bond.cxx
    src/H5Parser/Bond.h
    )


ADD_LIBRARY( libH5Parser STATIC ${H5Parser} )
include_directories(${PROJECT_SOURCE_DIR}/src)
set(MY_LIBS -lpthread -lstdc++fs libH5Parser ${VTK_LIBRARIES}  ${HDF5_LIBRARIES} )



add_executable(${PROJECT_NAME} "main.cxx" "src/utils/cxxopts.hpp" )
target_link_libraries(${PROJECT_NAME} ${MY_LIBS})
