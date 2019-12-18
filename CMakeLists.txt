cmake_minimum_required(VERSION 2.8)

project(DEM-POST)


FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

find_package(HDF5)
include_directories(${HDF5_INCLUDE_DIR})



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(modules
    src/core/Boundary.cxx
    src/core/Boundary.h
    src/core/Dataset.cxx
    src/core/Dataset.h
    src/core/Particle.cxx
    src/core/Particle.h
    src/core/AModule.cxx
    src/core/AModule.h

    src/core/CSVRow.cxx
    src/core/CSVRow.h

    src/core/Bond.h
    src/core/Bond.cxx

    src/core/BondGenerator.h
    src/core/BondGenerator.cxx

    src/modules/ModuleFactory.cxx
    src/modules/ModuleFactory.h
    src/core/ParsingParameters.cxx
    src/core/ParsingParameters.h


    src/modules/GlobalParameters.cxx
    src/modules/GlobalParameters.h
    src/modules/Boundaries.cxx
    src/modules/Boundaries.h
    src/modules/IndividualParticles.h
    src/modules/IndividualParticles.cxx
    src/modules/LineStrain.cxx
    src/modules/LineStrain.h
    src/modules/ParticleFixes.cxx
    src/modules/ParticleFixes.h

    src/modules/ContactInformation.cxx
    src/modules/ContactInformation.h

    src/modules/MeshCell.cxx
    src/modules/MeshCell.h

    src/modules/BondsInformation.cxx
    src/modules/BondsInformation.h

    )


ADD_LIBRARY( modules STATIC ${modules} )
include_directories(${PROJECT_SOURCE_DIR}/src)
set(MY_LIBS -lpthread -lstdc++fs modules ${VTK_LIBRARIES}  ${HDF5_LIBRARIES} )



add_executable(${PROJECT_NAME} "main.cxx" "src/utils/cxxopts.hpp" )
target_link_libraries(${PROJECT_NAME} ${MY_LIBS})
