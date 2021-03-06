cmake_minimum_required(VERSION 3.0)
project(HOWARD11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

if(MSVC)
    message("Compiling with MSVC, well maybe it's unsupported")
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif(MSVC)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Compiling with Clang ...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    message("Compiling with GNU-like CXX compiler ...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

include_directories(SYSTEM src)

set(PATH_PHYSXSDK /Users/secondwtq/Documents/PhysX-3.3/PhysXSDK)
include_directories(${PATH_PHYSXSDK}/Include)
link_directories(${PATH_PHYSXSDK}/Lib/osx64)

set(LIBS_PHYSX PhysX3CommonDEBUG SimulationControllerDEBUG
        LowLevelDEBUG PvdRuntimeDEBUG PhysX3DEBUG SceneQueryDEBUG
        PhysXProfileSDKDEBUG PhysX3ExtensionsDEBUG LowLevelClothDEBUG
        PhysXVisualDebuggerSDKDEBUG PxTaskDEBUG PhysX3CookingDEBUG
        PhysX3CharacterKinematicDEBUG)

# stackoverflow.com/questions/4346412/how-to-prepend-all-filenames-on-the-list-with-common-path
function(prepend var prefix)
    set(listVar "")
    foreach(f ${ARGN})
        list(APPEND listVar "${prefix}/${f}")
    endforeach(f)
    set(${var} "${listVar}" PARENT_SCOPE)
endfunction(prepend)

set(SOURCE_FSM FSM.hxx FSM.cxx FSMProxyTemplates.hxx FSMStream.hxx
    FSMCommon.hxx FSMLogger.hxx FSMHelper.hxx)

set(SOURCE_VERDANDI GLCommon.hxx GLFoundation.hxx GLFoundation.cxx
    GLShader.hxx GLShader.cxx GLHelper.cxx GLShaderExt.hxx GLVertexArray.cxx
    GLShaderExtDef.hxx GLVertexBuffer.hxx GLVertexArray.hxx
        GLVertexBufferExt.hxx GLHelper.hxx)

set(SOURCE_STANNUM StannumCommon.hxx Stannum.hxx Stannum.cxx StannumShaderCache.hxx
    StannumShaderCache.cxx StannumTexture.hxx StannumTexture.cxx StannumSprite.hxx
    StannumAtlasNode.cxx StannumAtlasNode.hxx StannumSpriteShader.cxx StannumSpriteShader.hxx
        StannumTextureAtlas.cxx StannumTextureAtlas.hxx)

set(SOURCE_DWIGHT HowardBase.hxx Node.hxx Node.cxx Handle.hxx
    RootNode.hxx HandleManager.hxx SceneManager.hxx ScriptNode.hxx
    StannumSpriteNode.hxx Event.hxx ScriptEvent.hxx InputEvent.hxx
    Observers.hxx ObserversDef.hxx EventAndObservers.cxx
    DwightScript.cxx Foundation.hxx)

set(SOURCE_FACERCORE FacerEvent.hxx FacerEventKey.hxx FacerEvent.cxx
    FacerEventPortGLFW.hxx FacerEventPortGLFW.cxx)

set(SOURCE_THIRDPT howardgl.hxx stb.cxx mozjs.hxx physx.hxx stb_image.hxx stb_image_resize.hxx)

set(SOURCE_MISC Transform.hxx Transform.cxx hassert.hxx AtTheVeryBeginning.hxx AtTheVeryBeginning.cxx
    Frustum.cxx Frustum.hxx)

set(SOURCE_HAMMER Hammer.cxx HammerActorNode.cxx HammerTransform.cxx HammerGlue.cxx
    HammerPrimitiveBody.cxx HammerHeightfield.cxx Hammer.hxx HammerActorNode.hxx
    HammerTransform.hxx HammerGlue.hxx HammerPrimitiveBody.hxx HammerPreDef.hxx
    HammerHeightfield.hxx HammerPreDefPhysX.hxx HammerPreDefExternal.hxx)

set(SOURCE_DUNE Dune.cxx DuneShader.cxx DuneDispatchCommand.cxx DuneTextureCache.cxx
        Dune.hxx DuneCommon.hxx DuneShader.hxx DuneDispatchCommand.hxx DuneTextureCache.hxx)

set(SOURCE_GUARDIAN Guardian.cxx GuardianCommon.cxx GuardianShader.cxx GuardianCacheShader.cxx
        Guardian.hxx GuardianCommon.hxx GuardianShader.hxx GuardianCacheShader.hxx)

prepend(SOURCE_FSM "FSM" ${SOURCE_FSM})
prepend(SOURCE_VERDANDI Verdandi ${SOURCE_VERDANDI})
prepend(SOURCE_STANNUM Stannum ${SOURCE_STANNUM})
prepend(SOURCE_DWIGHT Dwight ${SOURCE_DWIGHT})
prepend(SOURCE_FACERCORE FacerCore ${SOURCE_FACERCORE})
prepend(SOURCE_THIRDPT thirdpt ${SOURCE_THIRDPT})
prepend(SOURCE_MISC Misc ${SOURCE_MISC})
prepend(SOURCE_HAMMER Hammer ${SOURCE_HAMMER})
prepend(SOURCE_DUNE Dune ${SOURCE_DUNE})
prepend(SOURCE_GUARDIAN Guardian ${SOURCE_GUARDIAN})

set(SOURCE_ALL ${SOURCE_ALL} ${SOURCE_FSM} ${SOURCE_VERDANDI} ${SOURCE_STANNUM} ${SOURCE_DWIGHT}
    ${SOURCE_FACERCORE} ${SOURCE_THIRDPT} ${SOURCE_MISC} ${SOURCE_HAMMER} ${SOURCE_DUNE} ${SOURCE_GUARDIAN})

set(SOURCE_OTHER src/Debug.hxx src/Common.hxx src/Asset.hxx src/Entry.cxx src/Acheron.hxx
        src/GLFWEvents.hxx src/GLFWEvents.cxx src/JSFunctions.hxx src/JSFunctions.cxx
        src/CABAL/CABAL.hxx src/CABAL/CABAL.cxx src/Asset.cxx)

prepend(SOURCE_ALL src ${SOURCE_ALL})

add_executable(HOWARD11 ${SOURCE_ALL} ${SOURCE_OTHER} src/Misc/hash_fix.hxx src/Dwight/Observers.hxx src/Dwight/EventAndObservers.cxx)

set(HOWARD_LIBS ${HOWARD_LIBS} glfw3)
set(HOWARD_LIBS ${HOWARD_LIBS} confuse)
set(HOWARD_LIBS ${HOWARD_LIBS} mozjs-31)
set(HOWARD_LIBS ${HOWARD_LIBS} ${LIBS_PHYSX})

if(APPLE)

    find_library(FRAMEWORK_COCOA Cocoa)
    find_library(FRAMEWORK_GL OpenGL)
    find_library(FRAMEWORK_IOKIT IOKit)
    find_library(FRAMEWORK_CORE_VIDEO CoreVideo)
    set(EXTRA_LIBS_APPLE ${FRAMEWORK_COCOA} ${FRAMEWORK_GL} ${FRAMEWORK_IOKIT}
        ${FRAMEWORK_CORE_VIDEO})

    set(HOWARD_LIBS ${HOWARD_LIBS} ${EXTRA_LIBS_APPLE})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pagezero_size 10000 -image_base 100000000")

endif(APPLE)

target_link_libraries(HOWARD11 ${HOWARD_LIBS})
